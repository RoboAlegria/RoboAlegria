package com.android.sofla.drj;

import android.content.SharedPreferences;
import android.graphics.Canvas;
import android.graphics.RectF;

class Droid {

	float x;
	float y;
	float vy;
	boolean jumping;
	boolean falling;
	
	float w;
	float h;
	
	double v0;
	double a;
	
	final float startX;
	final float startY;
	final float initialVelocity;
	
	Game game;

	//
	// workshop 2
	//
	
	RectF rect;
	
	int curFrame;
	long curFrameTime = 0;
	
	// -- END workshop 2

	public Droid(Game game) {
		updateRobot("vel=50");
		
		this.game = game;
		startY = this.game.groundY - game.droidJumpImage.getHeight() + game.roadImage.getHeight()/2;
		startX = 180.0f * game.screenwidth/1280.0f;
		initialVelocity = 40.0f;
				
		//
		// workshop 2
		//
		this.rect = new RectF();
		
		w = 0.5f * game.droidJumpImage.getWidth();
		h = 0.6f * game.droidJumpImage.getHeight();
		
		// -- END workshop 2
		
		reset();
	}

	public void reset() {
		
		jumping = false;
		falling = false;
		
		x = startX;
		y = startY;
		
		rect.left = x;
		rect.top = y;
		rect.bottom = y + h;
		rect.right = x + w;
		
		curFrame = 0;
		curFrameTime = System.currentTimeMillis();
		
		updateRobot("fac=70");
	}

	public void update() {

		//
		// first: handle collision detection with items and potholes
		//		
		doCollisionDetection();

		//
		// handle falling
		//
		if (falling) {
			doPlayerFall();
		}

		//
		// handle jumping
		//
		if (jumping) {
			doPlayerJump();
		}

		//
		// does player want to jump?
		//
		if (game.playerTap && !jumping && !falling) {
			startPlayerJump();
			game.soundPool.play(game.droidJumpSnd, 1.0f, 1.0f, 0, 0, 1.0f);
		}
		
		//
		// workshop 2
		//
		
		//
		// update animation
		//
		long now = System.currentTimeMillis() - curFrameTime;
		if (now > 250) {
			curFrame++;
			if (curFrame > 3) {
				curFrame = 1;
			}
			curFrameTime = System.currentTimeMillis();
		}
		
		//update invencibility
		if ((System.currentTimeMillis() - game.starDurationTime) > 5000) {
			game.invencibility = false;
		}
		
		// -- END workshop 2
	}

	public void draw(Canvas canvas) {
		//canvas.drawRect(x, y, x + w, y + h, game.greenPaint);
		
		//
		// workshop 2
		//
		if (this.game.invencibility == false) {
			if (this.game.curLife > 2) {
				if (jumping || falling) {
					canvas.drawBitmap(game.droidJumpImage, x, y, game.clearPaint);
				}
				else {
					canvas.drawBitmap(game.droidImages[curFrame], x, y, game.clearPaint);
				}
			}
			else {
				if (jumping || falling) {
					canvas.drawBitmap(game.baddroidJumpImage, x, y, game.clearPaint);
				}
				else {
					canvas.drawBitmap(game.baddroidImages[curFrame], x, y, game.clearPaint);
				}
			}
		}
		else {
				if (jumping || falling) {
					canvas.drawBitmap(game.naldodroidJumpImage, x, y, game.clearPaint);
				}
				else {
					canvas.drawBitmap(game.naldodroidImages[curFrame], x, y, game.clearPaint);
				}
		}
				
		
		// -- END workshop 2
	}
	
	//
	// helper methods for workshop - not to be implemented by participants
	//
	private void doCollisionDetection() {

//		float ey = y + h;

		for (Pothole p : game.potholes) {
			if (!p.alive) {
				continue;
			}

			float lx = x;
			float rx = x + w;

			if (
					// am I over the pothole?
					(p.x < lx) 
					
					// am I still inside the pothole?
					&& ((p.x + p.w) > rx) 
					
					// have I fallen into the pothole?
					//&& (p.y <= ey)
					&& (p.y <= (y+h/0.6f))
				
				) {
				updateRobot("fac=60");
				game.initGameOver();				
			}
		}
		
		//
		// workshop 2
		//
		
		//
		// check for item collision
		//
		rect.left = x;
		rect.top = y;
		rect.bottom = y + h;
		rect.right = x + w;
		
		if (game.gooditem.alive && rect.intersect(game.gooditem.rect)) {
			updateRobot("fac=20");
			game.doPlayerEatGoodItem();			
		}
		if (game.baditem.alive && rect.intersect(game.baditem.rect)) {
			updateRobot("fac=40");
			game.doPlayerEatBadItem();
		}
		if (game.star.alive && rect.intersect(game.star.rect)) {
			updateRobot("mov=80");
			game.doPlayerEatStar();			
		}
		
		// -- END workshop 2
	}
	
	private void doPlayerFall() {
		vy += 0.5f + (a/1000.0f);
		y += vy;
		float tmpY = y + h/0.6f;
		if (tmpY > game.groundY) {
			y = startY;
			falling = false;
		}		
	}
	
	private void doPlayerJump() {
		y -= vy;
		vy -= 3.0f;
		if (vy <= 0.0f) {
			jumping = false;
			falling = true;
		}		
	}
	
	private void startPlayerJump() {
		jumping = true;
		game.playerTap = false;
		vy = initialVelocity;
		updateRobot("mov=30");
	}
	
	public void updateRobot(String command) {
		SendCommands commands = new SendCommands();
		commands.execute(command);
	}

	
	//
	// workshop 2
	//

	public void restore(SharedPreferences savedState) {
		x = savedState.getFloat("droid_x", 0);
		y = savedState.getFloat("droid_y", 0);
		vy = savedState.getFloat("droid_vy", 0);
		jumping = savedState.getBoolean("droid_jumping", false);
		falling = savedState.getBoolean("droid_falling", false);			
		curFrame = savedState.getInt("droid_curFrame", 0);
		curFrameTime = savedState.getLong("droid_curFrameTime",0 );		
	}
	
	public void save(SharedPreferences.Editor map) {
		map.putFloat("droid_x", x);
		map.putFloat("droid_y", y);
		map.putFloat("droid_vy", vy);
		map.putBoolean("droid_jumping", jumping);
		map.putBoolean("droid_falling", falling);
		map.putInt("droid_curFrame", curFrame);
		map.putLong("droid_curFrameTime", curFrameTime);
	}
	
	// -- END workshop 2
}
