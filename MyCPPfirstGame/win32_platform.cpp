
#include <windows.h>
#include <windowsx.h>
#include <wingdi.h>
#include <mmsystem.h>
#include <chrono>
#include <thread>


#define Window_width 640
#define Window_height 360
#define square_length 100
#define dis_from_left_corner 10
const COLORREF BackgroundColor = RGB(0, 0, 0);
const COLORREF BoardColor = RGB(255, 255,255);

#include "GamePlay.cpp"
#include "paint.cpp"
#include "AI.cpp"

bool running = true;
HWND logo,New_Game_Button,vs_PC_button,first_player_score,sec_player_score,tie_score, pause_button, resume_button;

enum Mode { None,TwoPlayers, vsPC };
int gameMode = None;
square* randomedSquare;




LRESULT CALLBACK Window_callback(HWND   hwnd, UINT   uMsg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY: {//when "exit" button is pressed
		running = false;
		PostQuitMessage(0);
	} break;

	case WM_LBUTTONDOWN: {//when left-mouse button is pressed
		if (gameMode!=None){

			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (xPos >= board[i][j].x && xPos <= board[i][j].x + square_length
						&& yPos >= board[i][j].y && yPos <= board[i][j].y + square_length && board[i][j].state == blank) {
						if (gameMode==vsPC) {
							board[i][j].state = X;
							Player_turn = pc;
							int temp = -1;
							if (!board_is_full() && !Check_Winner(temp)){
								//level_one();
								//level_two();
								
								level_three();
							}
								
							
						}
						else if (gameMode==TwoPlayers) {
							if (Player_turn == first) {
								board[i][j].state = X;
								Player_turn = second;
							}

							else if (Player_turn == second)
							{

								board[i][j].state = O;
								Player_turn = first;
							}
						}

					}



				}
			}
			InvalidateRect(hwnd, NULL, TRUE);
		}
		
			
	}break;


	case WM_PAINT: {
		hdc = BeginPaint(hwnd, &ps);

		paint_background(hdc, ps, BackgroundColor);
		draw_board(hdc, BoardColor);

		HFONT hFont = CreateFont(19, 0, 0, 0, FW_EXTRABOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
			OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, TEXT("Calbiri"));
		SendMessage(first_player_score, WM_SETFONT, (WPARAM)hFont, TRUE);
		SendMessage(sec_player_score, WM_SETFONT, (WPARAM)hFont, TRUE);
		SendMessage(tie_score, WM_SETFONT, (WPARAM)hFont, TRUE);
		
		draw_updated_board(hdc);
		


		
			
				

				
				
		
		
		
		int player_number=-1;
		wchar_t gameStatus[20];
		if (Check_Winner(player_number) || board_is_full()) {
			
			if (Check_Winner(player_number)) {
				if (player_number == X)
				{
					XScore++;
					wsprintf(gameStatus, L"%s", L"Player 1 Won!");
					wsprintf(FPS, L"%s\n%i", L"Player 1 (X)", XScore);
					SetWindowText(first_player_score, FPS);
				}

				else if (player_number == O)
				{
					OScore++;
					if (gameMode == vsPC)
					{
						wsprintf(SPS, L"%s\n %i", L"Computer", OScore);
					}
					else {
						wsprintf(SPS, L"%s\n %i", L"Player 2 (O)", OScore);
					}
					
					SetWindowText(sec_player_score, SPS);
					wsprintf(gameStatus, L"%s", L"Player 2 Won!");
				}

				

			}
			else if (board_is_full()) {
				TScore++;
				wsprintf(TS, L"%s\n %i", L"Tie", TScore);
				SetWindowText(tie_score, TS);
				wsprintf(gameStatus, L"%s", L"Draw!");
			}
			
			::MessageBox(hwnd, gameStatus, TEXT("Game result"), MB_OK);
			reset_game();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		
		

		DeleteObject(hFont);
		EndPaint(hwnd, &ps);

	} break;

		case WM_CREATE: {//making labels and buttons
			HBITMAP bitMapLogo = (HBITMAP)LoadImage(NULL, L"logo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			HBITMAP bitMapPlayFriend = (HBITMAP)LoadImage(NULL, L"PlayFriend.bmp", IMAGE_BITMAP, 200, 31, LR_LOADFROMFILE);
			HBITMAP bitMapPlayPC = (HBITMAP)LoadImage(NULL, L"PlayPC.bmp", IMAGE_BITMAP, 200, 31, LR_LOADFROMFILE);
			logo = CreateWindow(L"STATIC", NULL,
				WS_CHILD | WS_VISIBLE | SS_BITMAP,340, 10, NULL, NULL,
				hwnd, 0, 0, 0);//for button its BS_BITMAP
			SendMessageW(logo,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)bitMapLogo);
			New_Game_Button = CreateWindow(L"BUTTON", L"",
				WS_CHILD  | WS_VISIBLE | BS_BITMAP, 375, 85, 200, 31,
				hwnd, (HMENU)3, 0, 0);
			SendMessageW(New_Game_Button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitMapPlayFriend);
			vs_PC_button= CreateWindow(L"BUTTON", L"",
				WS_CHILD | WS_VISIBLE | BS_BITMAP,375, 120, 200, 31,
				hwnd, (HMENU)4, 0, 0);
			SendMessageW(vs_PC_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitMapPlayPC);
			wsprintf(FPS, L"%s\n%i", L"Player 1 (X) ", XScore);
			wsprintf(SPS, L"%s\n %i", L"Player 2 (O)", OScore);
			wsprintf(TS, L"%s\n %i", L"Tie", TScore);
			

			first_player_score = CreateWindow(L"STATIC", FPS,
				WS_CHILD | WS_VISIBLE, 350, 200, 90,35,
				hwnd, 0, 0, 0);
			tie_score = CreateWindow(L"STATIC", TS,
				WS_CHILD | WS_VISIBLE, 462, 200, 30, 35,
				hwnd, 0, 0, 0);
			sec_player_score = CreateWindow(L"STATIC", SPS,
				WS_CHILD | WS_VISIBLE, 520, 200, 90, 35,
				hwnd, 0, 0, 0);

			
			
		} break;

		case WM_COMMAND: {
			switch (LOWORD(wParam))
			{
				case 1:
				{
					//waveOutPause();
				}break;
				case 2:
				{
					//waveOutRestart();
				}break;
				case 3:
				{
					gameMode = TwoPlayers;
					reset_score();
					SetWindowText(first_player_score, FPS);
					SetWindowText(sec_player_score, SPS);
					SetWindowText(tie_score, TS);
					reset_game();
					InvalidateRect(hwnd, NULL, TRUE);
					::MessageBox(hwnd, L"Good Luck!", TEXT("2 Players mode"), MB_OK);

				}break;
				case 4:
				{
					gameMode = vsPC;
					reset_score();
					SetWindowText(first_player_score, FPS);
					wsprintf(SPS, L"%s\n %i", L"Computer", OScore);
					SetWindowText(sec_player_score, SPS);
					SetWindowText(tie_score, TS);
					reset_game();
					InvalidateRect(hwnd, NULL, TRUE);
					::MessageBox(hwnd, L"Good Luck!", TEXT("vs Computer Mode"), MB_OK);

				}break;
			}
		}break;

		case WM_CTLCOLORSTATIC: {
		
			HDC hdcStatic = (HDC)wParam; // or obtain the static handle in some other way
			SetTextColor(hdcStatic, RGB(70, 130, 180)); // text color
			SetBkColor(hdcStatic, BackgroundColor);
			SetDCBrushColor(hdcStatic, BackgroundColor);
			return (LRESULT)GetStockObject(DC_BRUSH);
		}
		break;


	default: {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
	return 0;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	
	reset_game();

	//Create windows class
	WNDCLASS window_class = {}; //EMPTY CLASS
	window_class.style = CS_HREDRAW | CS_VREDRAW; //for redrawing the window vertically and horizontally
	window_class.lpszClassName = L"Tic Tac Toe";//class name
	window_class.lpfnWndProc = Window_callback;//what handles messages of the windows

	//Register class
	RegisterClass(&window_class);

	
	//Create window
	HWND window = CreateWindow(window_class.lpszClassName, window_class.lpszClassName, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_CLIPCHILDREN | WS_VISIBLE, 300, 180, Window_width, Window_height, 0, 0, hInstance, 0);
	
	PlaySound(TEXT("LOFImusic.wav"), NULL, SND_LOOP | SND_ASYNC);

	while (running) {

		MSG message;
		//reading all the messages and proccesing them:
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) //REMOVING the message after reading it
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

	}
	
}