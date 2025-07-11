/*
 * Copyright 2025 Fire-Forest-Souls-studio (https://github.com/Fire-Forest-Souls-studio)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef CODE_INTRODUCTION_H
#define CODE_INTRODUCTION_H

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Introduction
{
	private:
		static Introduction* m_class_obj;

		Introduction ();
        static Introduction* getClass();

	protected:
		static vector<Texture> m_texture;
		static vector<unsigned> m_u_frames;
		static vector<unsigned> m_u_frames_vertical;
		static vector<float> m_f_animation_speed;
		static RectangleShape m_rectangle_shape;
		static float m_f_frame;
        static Vector2u m_V2u_frame_size;

	public:
		static void start ();
		static void main ();

		static const RectangleShape& getRender ();
};

#endif
