package com.android.sofla.drj;

import java.util.Random;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.media.AudioManager;
import android.media.SoundPool;
import android.util.DisplayMetrics;


public class Game {

	int screenwidth;
	int screenheight;
	//
	// pothole resources
	//
	final int MAX_potholes = 10;
	float MIN_POTHOLE_WIDTH = 150.0f;
	float MAX_POTHOLE_WIDTH = 200.0f;
	Pothole [] potholes;
	
	// keep track of last spawned pothole
	Pothole lastPothole;
	
	long spawnPotholeTime;
	final long SPAWN_POTHOLE_TIME = 3000;
	
	//
	// Droid/Player resources
	//
	Droid droid;
	float groundY;
	
	//
	// player input flag
	//
	boolean playerTap;

	//
	// possible game states
	//
	final int GAME_MENU = 0;
	final int GAME_READY = 1;
	final int GAME_PLAY = 2;
	final int GAME_OVER = 3;
	
	int gameState;

	//
	// game menu message
	//
	long tapToStartTime;
	boolean showTapToStart;
	
	//
	// get ready message
	//
	final int SHOW_GET_READY = 0;
	final int SHOW_GO = 1;
	
	long getReadyGoTime;
	int getReadyGoState;
	
	//
	// game over message
	//
	long gameOverTime;	

	//
	// shared paint objects for drawing
	//
	
	Paint greenPaint;
	Paint clearPaint;
	Paint darkPaint;
	Paint brownPaint;
	
	//
	// random number generator
	//
	Random rng;
	
	//
	// display dimensions
	//
	int width;
	int height;
	
	

	public Game(Context context) {
			
		//
		// allocate resources needed by game
		//
		
		DisplayMetrics metrics = context.getResources().getDisplayMetrics();
		screenwidth = metrics.widthPixels;
		screenheight = metrics.heightPixels;
		groundY = screenwidth/2;
		
		
		greenPaint = new Paint();
		greenPaint.setAntiAlias(true);
		greenPaint.setARGB(255, 0, 255, 0);
		greenPaint.setFakeBoldText(true);		
		greenPaint.setTextSize(42.0f);

		clearPaint = new Paint();
		clearPaint.setARGB(255, 240, 240, 240);
		clearPaint.setAntiAlias(true);
		
		darkPaint = new Paint();
		darkPaint.setARGB(255, 0, 0, 0);
		darkPaint.setAntiAlias(true);
		
		brownPaint = new Paint();
		brownPaint.setARGB(255, 199, 183, 153);
		brownPaint.setAntiAlias(true);
		
				
		rng = new Random();
		
		//
		// workshop 2
		//
		
		emptyPaint = new Paint();
		
		//
		// load images
		//

		loadImages(context);

		//
		// load sounds
		//
		
		//MediaPlayer mediaPlayer;
		soundPool = new SoundPool(4, AudioManager.STREAM_MUSIC, 0);
		loadSounds(context);
		
		
		
		// -- END workshop 2
		
		//
		// create game entities
		//
		
		droid = new Droid(this);
		
		potholes = new Pothole[MAX_potholes];
		for (int i=0; i<MAX_potholes; i++) {
			potholes[i] = new Pothole(i, this);
		}
		
		//
		// workshop 2
		//
		
		whitePaint = new Paint();
		whitePaint.setAntiAlias(true);
		whitePaint.setARGB(255, 255, 255, 255);
		whitePaint.setFakeBoldText(true);		
		whitePaint.setTextSize(42.0f);
		
		blackPaint = new Paint();
		blackPaint.setAntiAlias(true);
		blackPaint.setARGB(255, 0, 0, 0);
		blackPaint.setFakeBoldText(true);		
		blackPaint.setTextSize(42.0f);
				
		gooditem = new GoodItem(this);
		baditem = new BadItem(this);
		star = new Star(this);
		background = new BackGround(this);
		road = new Road(this);
		
		highScore = SCORE_DEFAULT;
		
		// -- END workshop 2
		
				
		//
		// initialize the game
		//
		resetGame();
	}
	
	public void setScreenSize(int width, int height) {
		this.width = width;
		this.height = height;
	}

	public void run(Canvas canvas) {
		switch (gameState) {
		case GAME_MENU:
			gameMenu(canvas);
			break;
		case GAME_READY:
			gameReady(canvas);
			break;
		case GAME_PLAY:
			gamePlay(canvas);
			break;
		case GAME_OVER:
			gameOver(canvas);
			break;
			
		//
		// workshop 2
		//
		case GAME_PAUSE:
			gamePause(canvas);
			break;
		}
		// -- END workshop 2
		
	}
	
	public void doTouch() {		
		playerTap = true;
	}

	public void resetGame() {
		tapToStartTime = System.currentTimeMillis();
		showTapToStart = true;
		
		playerTap = false;

		droid.reset();
		
		spawnPotholeTime = System.currentTimeMillis();
		for (Pothole p : potholes) {
			p.reset();
		}
		
		lastPothole = null;
		
		gameState = GAME_MENU;
		lastGameState = gameState;
		
		getReadyGoState = SHOW_GET_READY;
		getReadyGoTime = 0;
		
		//
		// workshop 2
		//
		
		curScore = 0;
		curLife = 3;
		invencibility = false;

		gooditem.reset();
		baditem.reset();
		background.reset();
		star.reset();
		spawnGoodItemTime = System.currentTimeMillis();
		spawnBadItemTime = System.currentTimeMillis();
		spawnStarTime = System.currentTimeMillis();
		starDurationTime = System.currentTimeMillis();
		
		road.reset();
		background.reset();
		
		// -- END workshop 2		
	}
	
	public void initGameOver() {
		
		gameState = GAME_OVER;
		gameOverTime = System.currentTimeMillis();
		
		//
		// workshop 2
		//
		
		// play droid crash sound
		soundPool.play(droidCrashSnd, 1.0f, 1.0f, 0, 0, 1.0f);
		
		// update high score
		if (curScore > highScore) {
			highScore = curScore;
		}
		
		// -- END workshop 2
	}

	private void gameOver(Canvas canvas) {

		// clear screen
		canvas.drawRect(0, 0, width, height, clearPaint);
		
		canvas.drawBitmap(gameoverImage, (screenwidth/2) - gameoverImage.getWidth()/2, screenheight/2 - gameoverImage.getHeight()/2, clearPaint);
		
		long now = System.currentTimeMillis() - gameOverTime;
		if (now > 2000) {
			resetGame();
		}
	}

	private void gamePlay(Canvas canvas) {
		
		// clear screen
		canvas.drawRect(0, 0, width, height, brownPaint);

		//
		// workshop 2
		//
		background.update();
		background.draw(canvas);
		
		// draw ground
		road.update();
		road.draw(canvas);
		
		// --- END workshop 2

		for (Pothole p : potholes) {
			if (p.alive) {
				p.update();
				p.draw(canvas);
			}
		}
		
		//
		// workshop 2
		//
		
		if (gooditem.alive) {
			gooditem.update();
			gooditem.draw(canvas);
		}
		
		if (baditem.alive) {
			baditem.update();
			baditem.draw(canvas);
		}
		
		if (star.alive) {
			star.update();
			star.draw(canvas);
		}
		
		// -- END workshop 2
		
		droid.update();
		droid.draw(canvas);
		
		if (curScore > 3000) {
			spawnPothole();
		}
		
		//
		// workshop 2
		//
		
		spawnGoodItem();
		spawnBadItem();
		spawnStar();
		
		doScore(canvas);
		
		// -- END workshop 2
	}

	private void gameReady(Canvas canvas) {
		
		//changeRobotFace("vel=50");
		
		long now;
		
		// clear screen
		canvas.drawRect(0, 0, width, height, brownPaint);
		background.draw(canvas);
		
		switch (getReadyGoState) {
		case SHOW_GET_READY:
			canvas.drawBitmap(prepararImage, (screenwidth/2) - prepararImage.getWidth()/2, screenheight/2 - prepararImage.getHeight()/2, clearPaint);
			now = System.currentTimeMillis() - getReadyGoTime;
			if (now > 1000) {
				getReadyGoTime = System.currentTimeMillis();
				getReadyGoState = SHOW_GO;
			}
			break;
		case SHOW_GO:
			canvas.drawBitmap(vaiImage, (screenwidth/2) - vaiImage.getWidth()/2, screenheight/2 - vaiImage.getHeight()/2, clearPaint);
			now = System.currentTimeMillis() - getReadyGoTime;
			if (now > 500) {				
				gameState = GAME_PLAY;
				
				//
				// workshop 2
				//
				scoreTime = System.currentTimeMillis();
				
				// -- END workshop 2				
			}
			break;
		}
		
		//
		// workshop 2
		//
		
		// draw ground
		road.draw(canvas);
		
		
		// -- END workshop 2
		
		// draw player
		droid.draw(canvas);
		
	}

	private void gameMenu(Canvas canvas) {

		canvas.drawRect(0, 0, width, height, clearPaint);

		canvas.drawBitmap(titleImage, (width/2) - titleImage.getWidth()/2, (height/2) - titleImage.getHeight()/2, clearPaint);
		
		canvas.drawBitmap(hiscoreImage, 0, 5, clearPaint);
		
		String highScoreString = "" + highScore;
		if (highScore == 0) {
			highScoreString = "000000";
		}
		if ((highScore > 0) && (highScore < 10)) {
			highScoreString = "00000"+highScoreString;
		}
		if ((highScore >= 10) && (highScore < 100)) {
			highScoreString = "0000"+highScoreString;
		}
		if ((highScore >= 100) && (highScore < 1000)) {
			highScoreString = "000"+highScoreString;
		}
		if ((highScore >= 1000) && (highScore < 10000)) {
			highScoreString = "00"+highScoreString;
		}
		if ((highScore >= 10000) && (highScore < 100000)) {
			highScoreString = "0"+highScoreString;
		}
		
		for (int i = 0; i < 6; i++) {
			char character = highScoreString.charAt(i);
			switch(character){
				case '0':
					canvas.drawBitmap(num0Image, hiscoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '1':
					canvas.drawBitmap(num1Image, hiscoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '2':
					canvas.drawBitmap(num2Image, hiscoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '3':
					canvas.drawBitmap(num3Image, hiscoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '4':
					canvas.drawBitmap(num4Image, hiscoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '5':
					canvas.drawBitmap(num5Image, hiscoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '6':
					canvas.drawBitmap(num6Image, hiscoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '7':
					canvas.drawBitmap(num7Image, hiscoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '8':
					canvas.drawBitmap(num8Image, hiscoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '9':
					canvas.drawBitmap(num9Image, hiscoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
			}
		}
		
		if (playerTap) {
			gameState = GAME_READY;
			playerTap = false;
			getReadyGoState = SHOW_GET_READY;
			getReadyGoTime = System.currentTimeMillis();

			// spawn 1st chasm so player sees something at start of game
			lastPothole = potholes[0];
			
		}

		long now = System.currentTimeMillis() - tapToStartTime;
		if (now > 550) {
			tapToStartTime = System.currentTimeMillis();
			showTapToStart = !showTapToStart;
		}

		if (showTapToStart) {
			canvas.drawBitmap(taptostartImage, (width/2) - taptostartImage.getWidth()/2, height-100.0f, clearPaint);
		}			
	}

	public float random(float a) {
		return rng.nextFloat() * a;
	}

	public float random(float a, float b) {		
		return Math.round(a + (rng.nextFloat() * (b - a)));
	}

	void spawnPothole() {
		long now = System.currentTimeMillis() - spawnPotholeTime;

		if (now > SPAWN_POTHOLE_TIME) {

			// randomly determine whether or not to spawn a new pothole
			if ((int)random(10) > 2) {
				
				//
				// find an available pothole to use
				//
				
				for (Pothole p : potholes) {
					
					if (p.alive) {
						continue;
					}
					
					//
					// by default all new potholes start just beyond
					// the right side of the display
					//
					
					float xOffset = 0.0f;
					
					//
					// if the last pothole is alive then use its width to adjust
					// the position of the new pothole if the last pothole
					// is too close to the right of the screen. this is to
					// give the player some breathing room.
					//
					
					if (lastPothole.alive) {
						
						float tmp = lastPothole.x + lastPothole.w;
						
						if (tmp > width) {
							tmp = tmp - width;
							xOffset = tmp + random(10.0f);
						}
						else {
							tmp = width - tmp;								
							if (tmp < 20.0f) {
								xOffset = tmp + random(10.0f);
							}
						}
					}

					p.spawn(xOffset);						
					lastPothole = p;						
					break;
				}
			}

			spawnPotholeTime = System.currentTimeMillis();
		}
	}
	
	//
	// workshop2
	//
	
	Paint whitePaint;
	Paint blackPaint;
	Paint emptyPaint;
	
	final int GAME_PAUSE = 4;
	
	//
	// track time between save games
	//
	long saveGameTime;
	
	//
	// hiscore
	//
	int highScore;
	int curScore;
	int curLife;
	boolean invencibility;
	
	long scoreTime;
	final long SCORE_TIME = 100;
	
	final int SCORE_DEFAULT = 0;
	final int SCORE_INC = 5;
	final int SCORE_ITEM_BONUS = 200;
	
	//
	// Itens
	//
	GoodItem gooditem;
	BadItem baditem;
	Star star;
	long spawnGoodItemTime;
	long spawnBadItemTime;
	long spawnStarTime;
	long starDurationTime;
	final long SPAWN_GOOD_ITEM_TIME = 1000;
	final long SPAWN_BAD_ITEM_TIME = 150;
	final long SPAWN_STAR_TIME = 5000;
	
	
	
	//
	// the road 
	//
	Road road;
	
	BackGround background;
	
	//
	// bitmaps
	//
	Bitmap titleImage;
	Bitmap taptostartImage;
	Bitmap hiscoreImage;
	Bitmap scoreImage;
	Bitmap lifeImage;
	Bitmap robotlifeImage;
	Bitmap gameoverImage;
	Bitmap pauseImage;
	Bitmap prepararImage;
	Bitmap vaiImage;
	Bitmap starImage;
	Bitmap roadImage;
	Bitmap backgroundImage;
	Bitmap dividerImage;
	Bitmap gooditemImage;
	Bitmap baditemImage;
	Bitmap droidJumpImage;
	Bitmap baddroidJumpImage;
	Bitmap naldodroidJumpImage;
	Bitmap num0Image;
	Bitmap num1Image;
	Bitmap num2Image;
	Bitmap num3Image;
	Bitmap num4Image;
	Bitmap num5Image;
	Bitmap num6Image;
	Bitmap num7Image;
	Bitmap num8Image;
	Bitmap num9Image;	
	Bitmap [] droidImages;
	Bitmap [] baddroidImages;
	Bitmap [] naldodroidImages;
	Bitmap [] gooditemImages;
	Bitmap [] baditemImages;
	final int MAX_DROID_IMAGES = 4;
	final int MAX_GOOD_IMAGES = 5;
	final int MAX_BAD_IMAGES = 5;
	
	//
	// sound
	//
	SoundPool soundPool;
	int droidJumpSnd;
	int droidEatGoodItemSnd;
	int droidEatBadItemSnd;
	int droidCrashSnd;

	int lastGameState;
	long pauseStartTime;
	
		
	private void loadSounds(Context context) {
		droidCrashSnd = soundPool.load(context, R.raw.droidcrash, 1);
		droidEatGoodItemSnd = soundPool.load(context, R.raw.eatgooditem, 1);
		droidEatBadItemSnd = soundPool.load(context, R.raw.droidcrash, 1);
		droidJumpSnd = soundPool.load(context, R.raw.droidjump, 1);
	}
	
	private void loadImages(Context context) {
		Resources res = context.getResources();
		
		roadImage = BitmapFactory.decodeResource(res, R.drawable.road);
		dividerImage = BitmapFactory.decodeResource(res, R.drawable.divider);
		
		backgroundImage = BitmapFactory.decodeResource(res, R.drawable.buildings5);
		
		titleImage = BitmapFactory.decodeResource(res, R.drawable.title3);
		taptostartImage = BitmapFactory.decodeResource(res, R.drawable.taptostart);
		hiscoreImage = BitmapFactory.decodeResource(res, R.drawable.hiscore2);
		scoreImage = BitmapFactory.decodeResource(res, R.drawable.score2);
		lifeImage = BitmapFactory.decodeResource(res, R.drawable.life);
		robotlifeImage = BitmapFactory.decodeResource(res, R.drawable.robot_life);
		gameoverImage = BitmapFactory.decodeResource(res, R.drawable.gameover);
		pauseImage = BitmapFactory.decodeResource(res, R.drawable.pause);
		prepararImage = BitmapFactory.decodeResource(res, R.drawable.preparar);
		vaiImage = BitmapFactory.decodeResource(res, R.drawable.vai);
		starImage = BitmapFactory.decodeResource(res, R.drawable.doutoresdaalegria);
		
		num0Image = BitmapFactory.decodeResource(res, R.drawable.num0);
		num1Image = BitmapFactory.decodeResource(res, R.drawable.num1);
		num2Image = BitmapFactory.decodeResource(res, R.drawable.num2);
		num3Image = BitmapFactory.decodeResource(res, R.drawable.num3);
		num4Image = BitmapFactory.decodeResource(res, R.drawable.num4);
		num5Image = BitmapFactory.decodeResource(res, R.drawable.num5);
		num6Image = BitmapFactory.decodeResource(res, R.drawable.num6);
		num7Image = BitmapFactory.decodeResource(res, R.drawable.num7);
		num8Image = BitmapFactory.decodeResource(res, R.drawable.num8);
		num9Image = BitmapFactory.decodeResource(res, R.drawable.num9);
		
		gooditemImages = new Bitmap[MAX_GOOD_IMAGES];
		gooditemImages[0] = BitmapFactory.decodeResource(res, R.drawable.banana);
		gooditemImages[1] = BitmapFactory.decodeResource(res, R.drawable.apple);
		gooditemImages[2] = BitmapFactory.decodeResource(res, R.drawable.strawberry);
		gooditemImages[3] = BitmapFactory.decodeResource(res, R.drawable.banana);
		gooditemImages[4] = BitmapFactory.decodeResource(res, R.drawable.orange);
		gooditemImage = gooditemImages[0];
		
		baditemImages = new Bitmap[MAX_BAD_IMAGES];
		baditemImages[0] = BitmapFactory.decodeResource(res, R.drawable.evil1);
		baditemImages[1] = BitmapFactory.decodeResource(res, R.drawable.evil2);
		baditemImages[2] = BitmapFactory.decodeResource(res, R.drawable.evil3);
		baditemImages[3] = BitmapFactory.decodeResource(res, R.drawable.evil1);
		baditemImages[4] = BitmapFactory.decodeResource(res, R.drawable.evil3);
		baditemImage = baditemImages[0];
		
		droidJumpImage = BitmapFactory.decodeResource(res, R.drawable.robo2);
		baddroidJumpImage = BitmapFactory.decodeResource(res, R.drawable.robo21);
		naldodroidJumpImage = BitmapFactory.decodeResource(res, R.drawable.robo002);
		
		droidImages = new Bitmap[MAX_DROID_IMAGES];		
		droidImages[0] = BitmapFactory.decodeResource(res, R.drawable.robo0);
		droidImages[1] = BitmapFactory.decodeResource(res, R.drawable.robo1);
		droidImages[2] = BitmapFactory.decodeResource(res, R.drawable.robo0);
		droidImages[3] = BitmapFactory.decodeResource(res, R.drawable.robo1);
		
		baddroidImages = new Bitmap[MAX_DROID_IMAGES];		
		baddroidImages[0] = BitmapFactory.decodeResource(res, R.drawable.robo01);
		baddroidImages[1] = BitmapFactory.decodeResource(res, R.drawable.robo11);
		baddroidImages[2] = BitmapFactory.decodeResource(res, R.drawable.robo01);
		baddroidImages[3] = BitmapFactory.decodeResource(res, R.drawable.robo11);
		
		naldodroidImages = new Bitmap[MAX_DROID_IMAGES];		
		naldodroidImages[0] = BitmapFactory.decodeResource(res, R.drawable.robo000);
		naldodroidImages[1] = BitmapFactory.decodeResource(res, R.drawable.robo001);
		naldodroidImages[2] = BitmapFactory.decodeResource(res, R.drawable.robo000);
		naldodroidImages[3] = BitmapFactory.decodeResource(res, R.drawable.robo001);
	}
	
	private void gamePause(Canvas canvas) {

		// clear screen
		canvas.drawRect(0, 0, width, height, clearPaint);
		
		canvas.drawBitmap(pauseImage, (screenwidth/2) - pauseImage.getWidth()/2, screenheight/2 - pauseImage.getHeight()/2, clearPaint);
		
		if (playerTap) {			
			playerTap = false;
			gameState = lastGameState;
			
			// determine time elapsed between pause and unpause
			long deltaTime = System.currentTimeMillis() - pauseStartTime;
			
			// adjust timer variables based on elapsed time delta 
			spawnPotholeTime += deltaTime;
			tapToStartTime += deltaTime;
			getReadyGoTime += deltaTime;
			gameOverTime += deltaTime;
			scoreTime += deltaTime;
			spawnGoodItemTime += deltaTime;
			spawnBadItemTime += deltaTime;
			spawnStarTime += deltaTime;
		}
	}
	
	public void pause() {
		
		// if game already paused don't pause it again - otherwise we'll lose the
		// game state and end up in an infinite loop
		if (gameState == GAME_PAUSE) {
			return;
		}
		
		lastGameState = gameState;
		gameState = GAME_PAUSE;
		pauseStartTime = System.currentTimeMillis();
	}
		
	void spawnGoodItem() {		
		long now = System.currentTimeMillis() - spawnGoodItemTime;

		if (now > SPAWN_GOOD_ITEM_TIME) {
			// randomly determine whether or not to spawn a new item
			if ((int)random(10) > 7) {				
				if (!gooditem.alive) {				
					gooditem.spawn();					
				}				
			}			
			spawnGoodItemTime = System.currentTimeMillis();
		}
	}
	
	void spawnBadItem() {		
		long now = System.currentTimeMillis() - spawnBadItemTime;

		if (now > SPAWN_BAD_ITEM_TIME/(curScore+1)) {
			// randomly determine whether or not to spawn a new item
			if ((int)random(10) > 7) {				
				if (!baditem.alive) {				
					baditem.spawn();					
				}				
			}			
			spawnBadItemTime = System.currentTimeMillis();
		}
	}
	
	void spawnStar() {		
		long now = System.currentTimeMillis() - spawnStarTime;

		if (now > SPAWN_STAR_TIME) {
			// randomly determine whether or not to spawn a new item
			if ((int)random(10) > 7) {				
				if (!star.alive) {				
					star.spawn();					
				}				
			}			
			spawnStarTime = System.currentTimeMillis();
		}
	}
	
	/*
	public void changeRobotFace(String command) {
		URL url;
	    HttpURLConnection urlConnection = null;
	    try {
	        url = new URL("http://192.168.201.3:80/?"+command);

	        urlConnection = (HttpURLConnection) url
	                .openConnection();
	        
	        urlConnection.setReadTimeout(10);
	        
	        InputStream in = urlConnection.getInputStream();
	        		        
	        urlConnection.disconnect();
	        
	    } catch (Exception e) {
	        e.printStackTrace();
	    } finally {
	        if (urlConnection != null) {
	            urlConnection.disconnect();
	        }    
	    }
	}
	*/
	
	public void doPlayerEatGoodItem() {
		// play sound
		soundPool.play(droidEatGoodItemSnd, 1.0f, 1.0f, 0, 0, 1.0f);
				
		// increase score
		curScore += SCORE_ITEM_BONUS;
		
		// increase life count
		curLife += 1;
		
		// reset spawn time
		gooditem.alive = false;
		spawnGoodItemTime = System.currentTimeMillis();		
	}
	
	public void doPlayerEatBadItem() {
		// play sound
		soundPool.play(droidEatBadItemSnd, 1.0f, 1.0f, 0, 0, 1.0f);
				
		// decrease life count
		if (invencibility == false) {
			curLife -= 1;
		}
		if (curLife == 0) {
			//update robot
			SendCommands commands = new SendCommands();
			commands.execute("fac=60");		
			this.initGameOver();
		}
		
		// reset spawn time
		baditem.alive = false;
		spawnBadItemTime = System.currentTimeMillis();
	}
	
	public void doPlayerEatStar() {
		// play sound
		soundPool.play(droidEatGoodItemSnd, 1.0f, 1.0f, 0, 0, 1.0f);
				
		// reset spawn time
		star.alive = false;
		invencibility = true;
		starDurationTime = System.currentTimeMillis();
		spawnStarTime = System.currentTimeMillis();
		
	}
	
	
	private void doScore(Canvas canvas) {
		
		// first update current score
		long now = System.currentTimeMillis() - scoreTime;
		
		if (now > SCORE_TIME) {
			curScore += SCORE_INC;
			scoreTime = System.currentTimeMillis();
		}
		
		// now draw it the screen
		canvas.drawBitmap(scoreImage, 0, 5, clearPaint);
//		StringBuilder buf = new StringBuilder(" ");
//		buf.append(curScore);		
//		canvas.drawText(buf.toString(), scoreImage.getWidth()+5, scoreImage.getHeight()+5, blackPaint);
		
//		canvas.drawBitmap(hiscoreImage, 0, 5, clearPaint);
		
		String scoreString = "" + curScore;
		if (curScore == 0) {
			scoreString = "000000";
		}
		if ((curScore > 0) && (curScore < 10)) {
			scoreString = "00000" + scoreString;
		}
		if ((curScore >= 10) && (curScore < 100)) {
			scoreString = "0000" + scoreString;
		}
		if ((curScore >= 100) && (curScore < 1000)) {
			scoreString = "000" + scoreString;
		}
		if ((curScore >= 1000) && (curScore < 10000)) {
			scoreString = "00" + scoreString;
		}
		if ((curScore >= 10000) && (curScore < 100000)) {
			scoreString = "0" + scoreString;
		}
		
		for (int i = 0; i < 6; i++) {
			char character = scoreString.charAt(i);
			switch(character){
				case '0':
					canvas.drawBitmap(num0Image, scoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '1':
					canvas.drawBitmap(num1Image, scoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '2':
					canvas.drawBitmap(num2Image, scoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '3':
					canvas.drawBitmap(num3Image, scoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '4':
					canvas.drawBitmap(num4Image, scoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '5':
					canvas.drawBitmap(num5Image, scoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '6':
					canvas.drawBitmap(num6Image, scoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '7':
					canvas.drawBitmap(num7Image, scoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '8':
					canvas.drawBitmap(num8Image, scoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
				case '9':
					canvas.drawBitmap(num9Image, scoreImage.getWidth() + (i)*num0Image.getWidth(), 5, clearPaint);
					break;
			}
		}

		
		
		// now draw it the screen
		//StringBuilder buf1 = new StringBuilder("VIDA: ");
		canvas.drawBitmap(lifeImage, 400, 5, clearPaint);
		for (int i = 1; i <= curLife; i++) {
			canvas.drawBitmap(robotlifeImage, 400 + lifeImage.getWidth() + (i-1)*robotlifeImage.getWidth()/2, 5, clearPaint);
		}
		//buf1.append(curLife);		
		//canvas.drawText(buf1.toString(), 400, 40, blackPaint);
		
	}
	
	public void restore(SharedPreferences savedState) {
		//
		// start restoring game variables
		//
		
		if (savedState.getInt("game_saved", 0) != 1) {
			return;
		}
		
		SharedPreferences.Editor editor = savedState.edit();
		editor.remove("game_saved");
		editor.commit();				
		
		highScore = savedState.getInt("game_highScore", SCORE_DEFAULT);
		
		int lastPotholeId = savedState.getInt("game_lastPotHole_id", -1);
		
		if (lastPotholeId != -1) {
			lastPothole = potholes[lastPotholeId];
			
		}
		else {
			lastPothole = null;
		}
		
		spawnPotholeTime = savedState.getLong("game_spawnPotholeTicks", 0);
		playerTap = savedState.getBoolean("game_playerTap", false);
		gameState = savedState.getInt("game_gameState", 0);
		tapToStartTime = savedState.getLong("game_tapToStartTime", 0);		
		showTapToStart = savedState.getBoolean("game_showTapToStart", false);
		getReadyGoTime = savedState.getLong("game_getReadyGoTime", 0);
		getReadyGoState = savedState.getInt("game_getReadyGoState", 0);
		gameOverTime = savedState.getLong("game_gameOverTime", 0);
		
		lastGameState = savedState.getInt("game_lastGameState", 1);
		pauseStartTime = savedState.getLong("game_pauseStartTime", 0);
		
		spawnGoodItemTime = savedState.getLong("game_spawnGoodItemTime", 0);
		spawnBadItemTime = savedState.getLong("game_spawnBadItemTime", 0);
		spawnStarTime = savedState.getLong("game_spawnStarTime", 0);
		
		scoreTime = savedState.getLong("game_scoreTime", 0);
		curScore = savedState.getInt("game_curScore", 0);
		
		// restore game entities		
		droid.restore(savedState);
		
		for (Pothole p : potholes) {
			p.restore(savedState);
		}
		
		gooditem.restore(savedState);
		baditem.restore(savedState);
		star.restore(savedState);
		
		background.restore(savedState);
		
		road.restore(savedState);
	}
	
	public void save(SharedPreferences.Editor map) {
		
		if (map == null) {			
			return;
		}
		
		map.putInt("game_saved", 1);

		map.putInt("game_highScore", highScore);		
		
		// save game vars
		if (lastPothole == null) {
			map.putInt("game_lastPotHole_id", -1);
		}
		else {
			map.putInt("game_lastPotHole_id", lastPothole.id);
		}
		
		map.putLong("game_spawnPotholeTicks", spawnPotholeTime);
		map.putBoolean("game_playerTap", playerTap);
		map.putInt("game_gameState", gameState);
		map.putLong("game_tapToStartTime", tapToStartTime);
		map.putBoolean("game_showTapToStart", showTapToStart);
		map.putLong("game_getReadyGoTime", getReadyGoTime);
		map.putInt("game_getReadyGoState", getReadyGoState);
		map.putLong("game_gameOverTime", gameOverTime);

		map.putInt("game_lastGameState", lastGameState);
		map.putLong("game_pauseStartTime", pauseStartTime);
		
		map.putLong("game_spawnGoodItemTime", spawnGoodItemTime);
		map.putLong("game_spawnBadItemTime", spawnBadItemTime);
		map.putLong("game_spawnStarTime", spawnBadItemTime);
		
		map.putLong("game_scoreTime", scoreTime);
		map.putInt("game_curScore", curScore);
		
		// save game entities
		
		droid.save(map);
		
		for (Pothole p : potholes) {
			p.save(map);
		}
		
		gooditem.save(map);
		
		baditem.save(map);
		
		star.save(map);
		
		background.save(map);
		
		road.save(map);
		
		//
		// store saved variables
		//
		map.commit();
	}
}