/****************************************************************************
 * libwiigui Template
 * Tantric 2009
 *
 * demo.cpp
 * Basic template/demonstration of libwiigui capabilities. For a
 * full-featured app using many more extensions, check out Snes9x GX.
 ***************************************************************************/

#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ogcsys.h>
#include <unistd.h>
#include <wiiuse/wpad.h>
#include <fat.h>

#include "FreeTypeGX.h"
#include "video.h"
#include "audio.h"
#include "menu.h"
#include "input.h"
#include "filelist.h"
#include "demo.h"

FreeTypeGX *fontSystem;
struct SSettings Settings;
int ExitRequested = 0;

void ExitApp()
{
	ShutoffRumble();
	StopGX();
	exit(0);
}

void
DefaultSettings()
{
	Settings.LoadMethod = METHOD_AUTO;
	Settings.SaveMethod = METHOD_AUTO;
	sprintf (Settings.Folder1,"libwiigui/first folder");
	sprintf (Settings.Folder2,"libwiigui/second folder");
	sprintf (Settings.Folder3,"libwiigui/third folder");
	Settings.AutoLoad = 1;
	Settings.AutoSave = 1;
}

int
main(int argc, char *argv[])
{
	PAD_Init();
	WPAD_Init();
	InitVideo(); // Initialise video
	InitAudio(); // Initialize audio
	fatInitDefault(); // Initialize file system

	// read wiimote accelerometer and IR data
	WPAD_SetDataFormat(WPAD_CHAN_ALL,WPAD_FMT_BTNS_ACC_IR);
	WPAD_SetVRes(WPAD_CHAN_ALL, screenwidth, screenheight);

	// Initialize font system
	fontSystem = new FreeTypeGX();
	fontSystem->loadFont(font_ttf, font_ttf_size, 0);
	fontSystem->setCompatibilityMode(FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_PASSCLR | FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_NONE);

	InitGUIThreads();
	DefaultSettings();
	MainMenu(MENU_SETTINGS);
}
