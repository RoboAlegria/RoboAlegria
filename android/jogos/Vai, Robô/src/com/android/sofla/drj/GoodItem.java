package com.android.sofla.drj;

import java.util.Random;

import android.content.SharedPreferences;
import android.graphics.Canvas;
import android.graphics.RectF;

public class GoodItem {

	float x, y;
	float w, h;
	boolean alive;
	double freq;
	int i1;
	
	Game game;
	RectF rect;
	
	float currTime;
	float initTime = System.currentTimeMillis();

	public GoodItem(Game game) {		
		this.game = game;

		w = game.gooditemImage.getWidth();
		h = game.gooditemImage.getHeight();
		
		rect = new RectF();
	}
	
	public void reset() {		
		alive = false;
	}

	public void spawn() {				
		
		Random r = new Random();
		//int i1 = r.nextInt(game.MAX_GOOD_IMAGES);
		i1 = r.nextInt(game.MAX_GOOD_IMAGES);
		game.gooditemImage = game.gooditemImages[i1];
		h = game.gooditemImage.getHeight();
		
		x = game.width + w;
		
		Random r1 = new Random();
		int i2 = r1.nextInt(2);
		float f1;
		if (i2 == 1) {
			f1 = 25;
		}
		else {
			f1 = 170;
		}
		
		y = game.groundY - h - f1;
		
		rect.top = y;
		rect.bottom = y + h;
		alive = true;		
	}

	public void update() {
		
		//
		// item move from right to left
		//

		float a = this.game.curScore;
		x -= (5.0f + (a/1000.0f));
		rect.left = x;
		rect.right = x + w;
		
		if (game.curScore > 4000) {
			freq = freq + Math.PI/100;
			y =  (float) (game.groundY - h - (200-55) - ((200-55)/2)*Math.sin(freq));
			rect.top = y;
			rect.bottom = y + h;
		}
		
		//
		// if item beyond left hand side of display then disable it
		//
		if (x < -w) {
			alive = false;
		}
	}

	public void draw(Canvas canvas) {
		canvas.drawBitmap(game.gooditemImage, rect.left, rect.top, game.clearPaint);
	}
	
	public void restore(SharedPreferences savedState) {
		x = savedState.getFloat("ps_x", 0);
		y = savedState.getFloat("ps_y", 0);
		w = savedState.getFloat("ps_w", 0);
		h = savedState.getFloat("ps_h", 0);
		alive = savedState.getBoolean("ps_alive", false);
	}
	
	public void save(SharedPreferences.Editor map) {		
		map.putFloat("ps_x", x);
		map.putFloat("ps_y", y);
		map.putFloat("ps_w", w);
		map.putFloat("ps_h", h);
		map.putBoolean("ps_alive", alive);
	}
}