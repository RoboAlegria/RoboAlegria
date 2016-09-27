package com.android.sofla.drj;

import android.content.SharedPreferences;
import android.graphics.Canvas;


class Pothole {

	float x, y;
	float w, h;
	boolean alive;
	
	Game game;
	
	public void reset() {		
		alive = false;
	}

	public void spawn(float xOffset) {
		
		//
		// spawn a pothole starting beyond right side of the display
		// apply additional xOffset and vary the width of the pothole
		//
		
		w = game.random(game.MIN_POTHOLE_WIDTH, game.MAX_POTHOLE_WIDTH);
		x = game.width + w + xOffset;
		alive = true;
	}

	public void update() {
		
		//
		// potholes move from right to left
		//
		
		float a = this.game.curScore;
		x -= (5.0f + (a/1000.0f));
		
		//
		// if pothole beyond left hand side of display then disable it
		//
		if (x < -w) {
			alive = false;
		}
	}

	public void draw(Canvas canvas) {
		canvas.drawRect(x, y, x + w, y + h, game.darkPaint);
	}

	//
	// workshop 2 code
	//
	
	int id;

	public Pothole(int id, Game game) {		
		this.id = id;
		this.game = game;
		y = game.groundY;
		h = game.roadImage.getHeight();
		alive = false;
	}	
	
	public void restore(SharedPreferences savedState) {
		x = savedState.getFloat("ph_" + id + "_x", 0);
		y = savedState.getFloat("ph_" + id + "_y", 0);
		w = savedState.getFloat("ph_" + id + "_w", 0);
		h = savedState.getFloat("ph_" + id + "_h", 0);
		alive = savedState.getBoolean("ph_" + id + "_alive", false);
	}
	
	public void save(SharedPreferences.Editor map) {		
		map.putFloat("ph_" + id + "_x", x);
		map.putFloat("ph_" + id + "_y", y);
		map.putFloat("ph_" + id + "_w", w);
		map.putFloat("ph_" + id + "_h", h);
		map.putBoolean("ph_" + id + "_alive", alive);
	}
}
