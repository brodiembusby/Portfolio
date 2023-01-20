#include<windows.h>
#include "button.cpp"
#include "utilities.cpp"

#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

WNDPROC Wndproc;

global_variable bool running = true;

struct Render_State {
	int height, width;
	void* memory;

	BITMAPINFO bitmap_info;
};


global_variable Render_State render_state;


internal void clear_screen(u32 color) {

	u32* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}

internal void draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y1 = clamp(0, y1, render_state.height);
	y0 = clamp(0, y0, render_state.height);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}
global_variable float render_scale = 0.01f;

internal void draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {

	x *= render_state.height* render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;


	//Change To Pixels
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;

	draw_rect_in_pixels(x0, y0, x1, y1, color);

}

float player1_pos_x = 10, player1_pos_y, player2_pos_x= 0, player2_pos_y,bullet_x;

float top_y =45, left_x=-90, right_x=90, bottom_y=-45,horizontal_size=91,vertical_size=45,size_wall=1;

internal void draw_map(u32 color) {
	//Top
	draw_rect(0, top_y, horizontal_size,size_wall, color);
	//Bottom
	draw_rect(0, bottom_y, horizontal_size,size_wall, color);
	//Far Left
	draw_rect(left_x, 0,size_wall, vertical_size, color);
	//Far Right
	draw_rect(right_x, 0,size_wall, vertical_size, color);


}
internal void simulate_game(Input* input,float dt) {
	clear_screen(0x000000);
	draw_map(0xFFFFFF);

	//Arena
	float speed = 50.f; // units per second
	if (is_down(BUTTON_UP)) player1_pos_y += speed * dt;
	if (is_down(BUTTON_DOWN)) player1_pos_y -= speed * dt;
	if (is_down(BUTTON_RIGHT)) player1_pos_x += speed * dt;
	if (is_down(BUTTON_LEFT)) player1_pos_x -= speed * dt;

	if (is_down(BUTTON_W)) player2_pos_y += speed * dt;
	if (is_down(BUTTON_S)) player2_pos_y -= speed * dt;
	if (is_down(BUTTON_D)) player2_pos_x += speed * dt;
	if (is_down(BUTTON_A)) player2_pos_x -= speed * dt;

	if (is_down(BUTTON_E))draw_rect(player2_pos_x+1 , player2_pos_y, 1, 1, 0x00ff7f);
	if (is_down(BUTTON_Q))draw_rect(player2_pos_x - 1, player2_pos_y, 1, 1, 0x00ff7f);

	if (is_down(BUTTON_PGUP))draw_rect(player1_pos_x + 1, player1_pos_y, .5, .5, 0x00ff7f);
	if (is_down(BUTTON_PGDOWN))draw_rect(player1_pos_x - 1, player1_pos_y, .5, .5, 0x00ff7f);
	
	draw_rect(player1_pos_x, player1_pos_y, 1, 1, 0x990000);
	draw_rect(player2_pos_x, player2_pos_y, 1, 1, 0xfff000);


}

LRESULT window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (uMsg) {
	case WM_CLOSE:

	case WM_DESTROY: {
		running = false;
	} break;

	case WM_SIZE: {
		RECT rect;
		GetClientRect(hwnd, &rect);
		 render_state.width = rect.right - rect.left;
		 render_state.height = rect.bottom - rect.top;

		int size = render_state.width * render_state.height * sizeof(u32);

		//If there is already memory reserved but incorrect, release it
		if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
		render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		
		//Details for buffer bitmap info
		render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
		render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
		render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
		render_state.bitmap_info.bmiHeader.biPlanes = 1;
		render_state.bitmap_info.bmiHeader.biBitCount = 32;
		render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;

	}
	default: {
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	}
	return result;
}
int WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nShowCmd)
 {
	
	// Create Window CLass
	WNDCLASS wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = L"Game Window Class";
	wc.lpfnWndProc = window_callback;
	// Register Class
	RegisterClass(&wc);
	// Create Window
	HWND window = CreateWindow(wc.lpszClassName, L"Pacman", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	//Handle for window
	HDC hdc = GetDC(window);

	Input input = {};

	float delta_time = 0.01666f;
	
	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);

	float performance_frequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performance_frequency = (float)perf.QuadPart;
	}

	while (running) {
		//Input
		MSG message;

		//reset button change
		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;

		}
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				//What key is being pressed
				u32 vk_code = (u32)message.wParam;
				//Is the key up or down
				bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b,vk)\
case vk: {\
input.buttons[b].changed = is_down != input.buttons[b].is_down;\
input.buttons[b].is_down = is_down;\
}break;
				switch (vk_code) {
					process_button(BUTTON_UP, VK_UP);
					process_button(BUTTON_DOWN, VK_DOWN);
					process_button(BUTTON_LEFT, VK_LEFT);
					process_button(BUTTON_RIGHT, VK_RIGHT);
					
					process_button(BUTTON_W, 'W');
					process_button(BUTTON_S, 'S');
					process_button(BUTTON_A, 'A');
					process_button(BUTTON_D, 'D');

					process_button(BUTTON_E, 'E');
					process_button(BUTTON_Q, 'Q');


					process_button(BUTTON_PGUP, VK_PRIOR);
					process_button(BUTTON_PGDOWN, VK_NEXT);

				}
			} break;


			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			}
		}

		//Simulate
		simulate_game(&input,delta_time);

		//Render
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height,render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		frame_begin_time = frame_end_time;

	}
	
}