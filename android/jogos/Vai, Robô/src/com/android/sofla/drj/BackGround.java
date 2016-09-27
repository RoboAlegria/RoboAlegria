package com.android.sofla.drj;

import android.content.SharedPreferences;
import android.graphics.Canvas;

public class BackGround {
	
	Game game;
	float y;
		
	final int MAX_DIVIDERS = 1;
	float [] bgdividerX;
		
	public BackGround(Game game) {
		this.game = game;
		y = game.groundY - game.backgroundImage.getHeight();
		
		bgdividerX = new float[MAX_DIVIDERS];		
	}
	
	public void reset() {
		float xOffset = 0.0f;		
		for (int i=0; i<MAX_DIVIDERS; i++) {
			bgdividerX[i] = xOffset; 			
		}		
	}
	
	public void update() {
		for (int i=0; i<MAX_DIVIDERS; i++) {
			float a = this.game.curScore;
			
			if (bgdividerX[i] <= - game.backgroundImage.getWidth()/2) { //-60.0f) {
				bgdividerX[i] = bgdividerX[i] + game.backgroundImage.getWidth()/2;//game.width + 10.0f*game.screenwidth/1280.0f;				
			}
			
			bgdividerX[i] -= (5.0f + (a/1000.0f));
			
		}
	}
	
	public void draw(Canvas canvas) {
		
		for (int i=0; i<MAX_DIVIDERS; i++) {			
			canvas.drawBitmap(game.backgroundImage, bgdividerX[i], y+10.0f, game.emptyPaint);			
		}		
	}
	
	public void restore(SharedPreferences savedState) {		
		for (int i=0; i<MAX_DIVIDERS; i++) {
			bgdividerX[i] = savedState.getFloat("bg_div_" + i + "_x", 0);
		}
	}
	
	public void save(SharedPreferences.Editor map) {
		for (int i=0; i<MAX_DIVIDERS; i++) {
			map.putFloat("bg_div_" + i + "_x", bgdividerX[i]);
		}
	}	
}
