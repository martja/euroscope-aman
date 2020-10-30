#pragma once
#if !defined(AMAN_CONSTANTS_H)
#define AMAN_CONSTANTS_H 1
#include <Windows.h>

const COLORREF AMAN_COLOR_TITLE_BAR_TEXT = RGB(255, 255, 255);
const COLORREF AMAN_COLOR_FIX_BACKGROUND = RGB(30, 30, 30);
const COLORREF AMAN_COLOR_FIX_TEXT = RGB(200, 200, 200);
const COLORREF AMAN_COLOR_TIME_TEXT = RGB(255, 255, 255);
const COLORREF AMAN_COLOR_AIRCRAFT_LABEL = RGB(255, 255, 255);
const COLORREF AMAN_COLOR_TRACKED = AMAN_COLOR_AIRCRAFT_LABEL;
const COLORREF AMAN_COLOR_UNTRACKED = RGB(150, 150, 150);

static const HBRUSH AMAN_BRUSH_MAIN_BACKGROUND = CreateSolidBrush(RGB(13, 9, 13));
static const HBRUSH AMAN_BRUSH_MENU_BACKGROUND = CreateSolidBrush(RGB(72, 72, 72));
static const HBRUSH AMAN_BRUSH_MENU_ICON_FILL = CreateSolidBrush(RGB(255, 255, 255));
static const HBRUSH AMAN_BRUSH_WINDOW_BUTTON_BACKGROUND = CreateSolidBrush(RGB(200, 200, 200));
static const HBRUSH AMAN_BRUSH_WINDOW_BUTTON_HOVERED_BACKGROUND = CreateSolidBrush(RGB(255, 255, 255));
static const HBRUSH AMAN_BRUSH_TIMELINE_AHEAD = CreateSolidBrush(RGB(115, 115, 115));

const HBRUSH AMAN_BRUSH_TIMELINE_PAST = CreateSolidBrush(RGB(72, 72, 72));
const HBRUSH AMAN_TRACKED_BRUSH = CreateSolidBrush(AMAN_COLOR_AIRCRAFT_LABEL);
const HBRUSH AMAN_UNTRACKED_BRUSH = CreateSolidBrush(AMAN_COLOR_UNTRACKED);

const HPEN AMAN_WHITE_PEN = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
const HPEN AMAN_VERTICAL_LINE_PEN = CreatePen(PS_SOLID, 1, RGB(180, 180, 180));
const HPEN AMAN_GRAY_PEN = CreatePen(PS_SOLID, 1, AMAN_COLOR_UNTRACKED);

const HFONT AMAN_TIME_FONT = CreateFont(13, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 3, 2, 1, 49, "EuroScope");
const HFONT AMAN_LABEL_FONT = CreateFont(13, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 3, 2, 1, 49, "EuroScope");
const HFONT AMAN_FIX_FONT = CreateFont(15, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 3, 2, 1, 49, "EuroScope");

const int AMAN_TITLEBAR_HEIGHT = 20;
const int AMAN_TIMELINE_WIDTH = 50;
const int AMAN_TIMELINE_TIME_POS = 40;
const int AMAN_TIMELINE_REALTIME_OFFSET = 50;
const int AMAN_WIDTH = 330;
const int AMAN_AIRCRAFT_LINE_HEIGHT = 12;
const int AMAN_LABEL_SEP_FROM_TIMELINE = 20;
const int AMAN_DOT_RADIUS = 3;

#endif
