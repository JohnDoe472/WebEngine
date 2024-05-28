#pragma once
#ifndef WEB_ENGINE_WINDOW_INPUT_KEY_HPP_
#define WEB_ENGINE_WINDOW_INPUT_KEY_HPP_

namespace WebEngine::Window::Input
{
    enum class EKey
    {
        eK_Unknown            = 0,

        eK_Return             = '\r',
        eK_Escape             = '\x1B',
        eK_Backspace          = '\b',
        eK_Tab                = '\t',
        eK_Space              = ' ',
        eK_Exclaim            = '!',
        eK_Quotedbl           = '"',
        eK_Hash               = '#',
        eK_Percent            = '%',
        eK_Dollar             = '$',
        eK_Ampersand          = '&',
        eK_Quote              = '\'',
        eK_Leftparen          = '(',
        eK_Rightparen         = ')',
        eK_Asterisk           = '*',
        eK_Plus               = '+',
        eK_Comma              = ',',
        eK_Minus              = '-',
        eK_Period             = '.',
        eK_Slash              = '/',
        eK_0                  = '0',
        eK_1                  = '1',
        eK_2                  = '2',
        eK_3                  = '3',
        eK_4                  = '4',
        eK_5                  = '5',
        eK_6                  = '6',
        eK_7                  = '7',
        eK_8                  = '8',
        eK_9                  = '9',
        eK_Colon              = ':',
        eK_Semicolon          = ';',
        eK_Less               = '<',
        eK_Equals             = '=',
        eK_Greater            = '>',
        eK_Question           = '?',
        eK_At                 = '@',
        eK_Leftbracket        = '[',
        eK_Backslash          = '\\',
        eK_Rightbracket       = ']',
        eK_Caret              = '^',
        eK_Underscore         = '_',
        eK_Backquote          = '`',
        eK_A                  = 'a',
        eK_B                  = 'b',
        eK_C                  = 'c',
        eK_D                  = 'd',
        eK_E                  = 'e',
        eK_F                  = 'f',
        eK_G                  = 'g',
        eK_H                  = 'h',
        eK_I                  = 'i',
        eK_J                  = 'j',
        eK_K                  = 'k',
        eK_L                  = 'l',
        eK_M                  = 'm',
        eK_N                  = 'n',
        eK_O                  = 'o',
        eK_P                  = 'p',
        eK_Q                  = 'q',
        eK_R                  = 'r',
        eK_S                  = 's',
        eK_T                  = 't',
        eK_U                  = 'u',
        eK_V                  = 'v',
        eK_W                  = 'w',
        eK_X                  = 'x',
        eK_Y                  = 'y',
        eK_Z                  = 'z',

        eK_Capslock           = '\x39',
        eK_F1                 = '\x3A',
        eK_F2                 = '\x3B',
        eK_F3                 = '\x3C',
        eK_F4                 = '\x3D',
        eK_F5                 = '\x3E',
        eK_F6                 = '\x3F',
        eK_F7                 = '\x40',
        eK_F8                 = '\x41',
        eK_F9                 = '\x42',
        eK_F10                = '\x43',
        eK_F11                = '\x44',
        eK_F12                = '\x45',

        eK_PrintScreen        = 1073741894,
        eK_Scrolllock         = 1073741895,
        eK_Pause              = 1073741896,
        eK_Insert             = 1073741897,
        eK_Home               = 1073741898,
        eK_PageUp             = 1073741899,
        eK_Delete             = '\x7F',
        eK_End                = 1073741901,
        eK_PageDown           = 1073741902,
        eK_Right              = 1073741903,
        eK_Left               = 1073741904,
        eK_Down               = 1073741905,
        eK_Up                 = 1073741906,

        eK_NumLockClear       = 1073741907,
        eK_KPDivide           = 1073741908,
        eK_KPMultiply         = 1073741909,
        eK_KPMinus            = 1073741910,
        eK_KPPlus             = 1073741911,
        eK_KPEnter            = 1073741912,
        eK_KP1                = 1073741913,
        eK_KP2                = 1073741914,
        eK_KP3                = 1073741915,
        eK_KP4                = 1073741916,
        eK_KP5                = 1073741917,
        eK_KP6                = 1073741918,
        eK_KP7                = 1073741919,
        eK_KP8                = 1073741920,
        eK_KP9                = 1073741921,
        eK_KP0                = 1073741922,
        eK_KPPeriod           = 1073741923,

        eK_Application        = 1073741925,
        eK_Power              = 1073741926,
        eK_KPEquals           = 1073741927,
        eK_F13                = 1073741928,
        eK_F14                = 1073741929,
        eK_F15                = 1073741930,
        eK_F16                = 1073741931,
        eK_F17                = 1073741932,
        eK_F18                = 1073741933,
        eK_F19                = 1073741934,
        eK_F20                = 1073741935,
        eK_F21                = 1073741936,
        eK_F22                = 1073741937,
        eK_F23                = 1073741938,
        eK_F24                = 1073741939,
        eK_Execute            = 1073741940,
        eK_Help               = 1073741941,
        eK_Menu               = 1073741942,
        eK_Select             = 1073741943,
        eK_Stop               = 1073741944,
        eK_Again              = 1073741945,
        eK_Undo               = 1073741946,
        eK_Cut                = 1073741947,
        eK_Copy               = 1073741948,
        eK_Paste              = 1073741949,
        eK_Find               = 1073741950,
        eK_Mute               = 1073741951,
        eK_VolumeUp           = 1073741952,
        eK_VolumeDown         = 1073741953,
        eK_KPComma            = 1073741957,
        eK_KPEqualSas400      = 1073741958,

        eK_AltErase           = 1073741977,
        eK_SysReq             = 1073741978,
        eK_Cancel             = 1073741979,
        eK_Clear              = 1073741980,
        eK_Prior              = 1073741981,
        eK_Return2            = 1073741982,
        eK_Separator          = 1073741983,
        eK_Out                = 1073741984,
        eK_Oper               = 1073741985,
        eK_ClearAgain         = 1073741986,
        eK_CRSel              = 1073741987,
        eK_Exsel              = 1073741988,

        eK_KP00               = 1073742000,
        eK_KP000              = 1073742001,
        eK_ThousandsSeparator = 1073742002,
        eK_DecimalSeparator   = 1073742003,
        eK_CurrencyUnit       = 1073742004,
        eK_CurrencySubUnit    = 1073742005,
        eK_KPLeftParen        = 1073742006,
        eK_KPRightParen       = 1073742007,
        eK_KPLeftBrace        = 1073742008,
        eK_KPRightBrace       = 1073742009,
        eK_KPTab              = 1073742010,
        eK_KPBackspace        = 1073742011,
        eK_KPA                = 1073742012,
        eK_KPB                = 1073742013,
        eK_KPC                = 1073742014,
        eK_KPD                = 1073742015,
        eK_KPE                = 1073742016,
        eK_KPF                = 1073742017,
        eK_KPXOR              = 1073742018,
        eK_KPPower            = 1073742019,
        eK_KPPercent          = 1073742020,
        eK_KPLess             = 1073742021,
        eK_KPGreater          = 1073742022,
        eK_KPAmpersand        = 1073742023,
        eK_KPDBLAmpersand     = 1073742024,
        eK_KPVerticalBar      = 1073742025,
        eK_KPDBLVerticalBar   = 1073742026,
        eK_KPColon            = 1073742027,
        eK_KPHash             = 1073742028,
        eK_KPSpace            = 1073742029,
        eK_KPAt               = 1073742030,
        eK_KPExclam           = 1073742031,
        eK_KPMemStore         = 1073742032,
        eK_KPMemRecall        = 1073742033,
        eK_KPMemClear         = 1073742034,
        eK_KPMemAdd           = 1073742035,
        eK_KPMemSubtract      = 1073742036,
        eK_KPMemMultiply      = 1073742037,
        eK_KPMemDivide        = 1073742038,
        eK_KPPlusMinus        = 1073742039,
        eK_KPClear            = 1073742040,
        eK_KPClearEntry       = 1073742041,
        eK_KPBinary           = 1073742042,
        eK_KPOctal            = 1073742043,
        eK_KPDecimal          = 1073742044,
        eK_KPHexadecimal      = 1073742045,

        eK_LCtrl              = 1073742048,
        eK_LShift             = 1073742049,
        eK_LAlt               = 1073742050,
        eK_LGUI               = 1073742051,
        eK_RCtrl              = 1073742052,
        eK_RShift             = 1073742053,
        eK_RAlt               = 1073742054,
        eK_RGUI               = 1073742055,

        eK_Mode               = 1073742081,

        eK_AudioNext          = 1073742082,
        eK_AudioPrev          = 1073742083,
        eK_AudioStop          = 1073742084,
        eK_AudioPlay          = 1073742085,
        eK_AudioMute          = 1073742086,
        eK_MediaSelect        = 1073742087,
        eK_WWW                = 1073742088,
        eK_Mail               = 1073742089,
        eK_Calculator         = 1073742090,
        eK_Computer           = 1073742091,
        eK_ACSearch           = 1073742092,
        eK_ACHome             = 1073742093,
        eK_ACBack             = 1073742094,
        eK_ACForward          = 1073742095,
        eK_ACStop             = 1073742096,
        eK_ACRefresh          = 1073742097,
        eK_ACBookmarks        = 1073742098,

        eK_BrightnessDown     = 1073742099,
        eK_BrightnesSUp       = 1073742100,
        eK_DisplaySwitch      = 1073742101,
        eK_KBDillumToggle     = 1073742102,
        eK_KBDillumDown       = 1073742103,
        eK_KBDillumUp         = 1073742104,
        eK_Eject              = 1073742105,
        eK_Sleep              = 1073742106,
        eK_App1               = 1073742107,
        eK_App2               = 1073742108,

        eK_AudioRewind        = 1073742109,
        eK_AudioFastForward   = 1073742110,

        eK_SoftLeft           = 1073742111,
        eK_SoftRight          = 1073742112,
        eK_Call               = 1073742113,
        eK_EndCalL            = 1073742114
    };
}

#endif // WEB_ENGINE_WINDOW_INPUT_KEY_HPP_