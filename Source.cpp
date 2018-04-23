#include <stdio.h>
#include <allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <fstream>
using namespace std;

bool pixelCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int Paddle_SIZE = 32;

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
enum MYKEYS2 {
	KEY_W, KEY_S, KEY_A, KEY_D
};
int main(int argc, char **argv) {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	ALLEGRO_BITMAP *Paddle = NULL;
	ALLEGRO_BITMAP *Paddle2 = NULL;
	ALLEGRO_BITMAP *Paddle3 = NULL;
	ALLEGRO_BITMAP *Paddle4 = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	cout << "PONG" << endl;
	// Paddle 1 left
	float Paddle_x = 20;
	float Paddle_y = 50;
	float Paddle_dx = -4.0, Paddle_dy = 4.0;

	//Paddle 2 right
	float Paddle2_x = 590;
	float Paddle2_y = 280;
	float Paddle2_dx = -2.0, Paddle2_dy = 4.0;

	// Paddle 3 top
	float Paddle3_x = 260;
	float Paddle3_y = 20;
	float Paddle3_dx = -4.0, Paddle3_dy = 4.0;

	// Paddle 4 bottom
	float Paddle4_x = 260;
	float Paddle4_y = 430;
	float Paddle4_dx = -4.0, Paddle4_dy = 4.0;

	//Ball
	float bouncer_x = 260;
	float bouncer_y = 200;

	//bouncer speed
	float bouncer_dx = -4.0, bouncer_dy = 4.0;


	bool key[4] = { false, false, false, false };
	bool key2[4] = { false, false, false, false };
	int score = -1;
	int score2 = -1;
	bool doexit = false;
	bool redraw = true;
	al_init();

	timer = al_create_timer(1.0 / FPS);

	al_install_keyboard();

	al_init_primitives_addon();

	al_init_font_addon();

	al_init_ttf_addon();

	display = al_create_display(SCREEN_W, SCREEN_H);

	font = al_load_ttf_font("Ice.ttf", 20, 0);

	//Ball
	bouncer = al_create_bitmap(25, 25);

	//Paddle 1
	Paddle = al_create_bitmap(32, 140);

	//Paddle 2
	Paddle2 = al_create_bitmap(32, 140);

	//Paddle 3
	Paddle3 = al_create_bitmap(140, 32);

	//Paddle 4
	Paddle4 = al_create_bitmap(140, 32);

	//Ball color
	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgb(255, 0, 0));

	//Paddle 1 color
	al_set_target_bitmap(Paddle);
	al_clear_to_color(al_map_rgb(0, 0, 255));

	//Paddle 2 color
	al_set_target_bitmap(Paddle2);
	al_clear_to_color(al_map_rgb(0, 0, 255));

	//Paddle 3 color
	al_set_target_bitmap(Paddle3);
	al_clear_to_color(al_map_rgb(0, 0, 255));

	//Paddle 4 color
	al_set_target_bitmap(Paddle4);
	al_clear_to_color(al_map_rgb(0, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();


	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);
	//save states
	int topscores[5];
	int highscores[5];
	ifstream scoreread;
	ifstream infile;
	int num;
	infile.open("Save.txt");
	int temp;

	for (int i = 0; i < 5; i++)
		infile >> topscores[i];

	for (int i = 0; i < 5; i++)
		cout << topscores[i] << endl;

	al_draw_text(font, al_map_rgb(250, 250, 250), 150, 50, ALLEGRO_ALIGN_CENTER, "Top Scores");

	for (int i = 0; i < 5; i++)

		al_draw_textf(font, al_map_rgb(250, 250, 250), 500, 50 + i * 40, ALLEGRO_ALIGN_CENTER, "%d", topscores[i]);

	al_flip_display();
	al_rest(5);

	while (!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		//pysical section
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			cout << "beginning timer section" << endl;
			//bounce the square against the sides of the game window
			if (bouncer_x < 0) {
				bouncer_dx = -bouncer_dx;
				score++;
			}

			if (bouncer_x > 640 - 32) {
				bouncer_dx = -bouncer_dx;
				score2++;
			}

			if (bouncer_y < 0 || bouncer_y > 480 - 32) {
				bouncer_dy = -bouncer_dy;
			}
			//add the x velocity to the x position, 
			//and the y velocity to the y position
			bouncer_x += bouncer_dx;
			bouncer_y += bouncer_dy;

			//paddle 1 up/down
			if (key2[KEY_W] && Paddle_y >= 4.0) {
				Paddle_y -= 4.0;
			}

			if (key2[KEY_S] && Paddle_y <= SCREEN_H - Paddle_SIZE - 4.0) {
				Paddle_y += 4.0;
			}

			//paddle 3 left right BROKEN
				if (key2[KEY_A] && Paddle3_x >= 4.0) {
			Paddle3_x -= 4.0;
			}

			if (key2[KEY_D] && Paddle3_x <= SCREEN_W - Paddle_SIZE - 4.0) {
				Paddle3_x += 4.0;
			}

			//paddle 2 BROKEN
			if (key[KEY_UP] && Paddle2_y >= 4.0) {
				Paddle2_y -= 4.0;
			}

			if (key[KEY_DOWN] && Paddle2_y <= SCREEN_H - Paddle_SIZE - 4.0) {
				Paddle2_y += 4.0;
			}


			//paddle 4
			if (key[KEY_RIGHT] && Paddle4_x <= SCREEN_W - Paddle_SIZE - 4.0) {
			Paddle4_x += 4.0;
			}

			if (key[KEY_LEFT] && Paddle4_x >4) {
			Paddle4_x -= 4.0;
			}

			redraw = true;

			if (pixelCollision(bouncer_x, bouncer_y, 32, 32, Paddle_x, Paddle_y, 32, 140)) {
				cout << "collision!";
				bouncer_dx = -bouncer_dx;//reflection

			}
			if (pixelCollision(bouncer_x, bouncer_y, 32, 32, Paddle2_x, Paddle2_y, 32, 140)) {
				cout << "collision!";
				bouncer_dx = -bouncer_dx;//reflection

			}
			if (pixelCollision(bouncer_x, bouncer_y, 32, 32, Paddle3_x, Paddle3_y, 140, 32)) {
				cout << "collision!";
				bouncer_dy = -bouncer_dy;//reflection

			}
			if (pixelCollision(bouncer_x, bouncer_y, 32, 32, Paddle4_x, Paddle4_y, 140, 32)) {
				cout << "collision!";
				bouncer_dy = -bouncer_dy;//reflection

			}
		}
		//I/O section: close game window if x is pressed//////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_W:
				key2[KEY_W] = true;
				break;

			case ALLEGRO_KEY_S:
				key2[KEY_S] = true;
				break;

				case ALLEGRO_KEY_A:
				key2[KEY_A] = true;
				break;

				case ALLEGRO_KEY_D:
				key2[KEY_D] = true;
				break;

			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

		    case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;


			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_W:
				key2[KEY_W] = false;
				break;

			case ALLEGRO_KEY_S:
				key2[KEY_S] = false;
				break;

			case ALLEGRO_KEY_A:
				key2[KEY_A] = false;
				break;

			case ALLEGRO_KEY_D:
				key2[KEY_D] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;

			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

				case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

				case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			}
		}


		//render section//////////////////////////////////////////////////////////////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			cout << "attempting to draw stuff" << endl;
			al_draw_bitmap(Paddle, Paddle_x, Paddle_y, 0);
			al_draw_bitmap(Paddle2, Paddle2_x, Paddle2_y, 0);
			al_draw_bitmap(Paddle3, Paddle3_x, Paddle3_y, 0);
			al_draw_bitmap(Paddle4, Paddle4_x, Paddle4_y, 0);
			al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
			al_draw_textf(font, al_map_rgb(250, 250, 250), 500, 50, ALLEGRO_ALIGN_CENTER, "%d", score);
			al_draw_textf(font, al_map_rgb(250, 250, 250), 150, 50, ALLEGRO_ALIGN_CENTER, "%d", score2);

			al_flip_display();

		}//end render

	}//end game loop

	ofstream write;
	write.open("Save.txt");

	for (int i = 0; i < 5; i++) {
		cout << "your highscore is " << topscores[i];
		if (score > topscores[i]) {
			temp = topscores[i];
			topscores[i] = score;
			score = temp;
			cout << "replacing sacores " << endl;
		}
	}
	//this part actually writes to the file
	for (int i = 0; i < 5; i++) {
		write << topscores[i] << endl;
	}
	al_rest(2);
	write.close();

	al_destroy_bitmap(bouncer);
	al_destroy_bitmap(Paddle);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);


	return 0;

}

bool pixelCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {

	if ((x1 + w1 > x2) && (x2 + w2 > x1) && (y2 + h2 > y1) && (y1 + h1 > y2))
		return true;

	else
		return false;



}


