/*_________
 /         \ tinyfiledialogsTest.cs v3.5.1 [Apr 18, 2020] zlib licence
 |tiny file| C# bindings created [2015]
 | dialogs | Copyright (c) 2014 - 2020 Guillaume Vareille http://ysengrin.com
 \____  ___/ http://tinyfiledialogs.sourceforge.net
      \|     git clone http://git.code.sf.net/p/tinyfiledialogs/code tinyfd
         ____________________________________________
	    |                                            |
	    |   email: tinyfiledialogs at ysengrin.com   |
	    |____________________________________________|

If you like tinyfiledialogs, please upvote my stackoverflow answer
https://stackoverflow.com/a/47651444
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

class tinyfd
{
    // windows only: to set char to UTF8 (instead of MBCS)
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CallingConvention = CallingConvention.Cdecl)]
    public static extern void tinyfd_setWinUtf8();

    // cross platform UTF8 (or MBCS on windows)
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CallingConvention = CallingConvention.Cdecl)]
    public static extern void tinyfd_beep();
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tinyfd_notifyPopup(string aTitle, string aMessage, string aIconType);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tinyfd_messageBox(string aTitle, string aMessage, string aDialogTyle, string aIconType, int aDefaultButton);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_inputBox(string aTitle, string aMessage, string aDefaultInput);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_saveFileDialog(string aTitle, string aDefaultPathAndFile, int aNumOfFilterPatterns, string[] aFilterPatterns, string aSingleFilterDescription);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_openFileDialog(string aTitle, string aDefaultPathAndFile, int aNumOfFilterPatterns, string[] aFilterPatterns, string aSingleFilterDescription, int aAllowMultipleSelects);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_selectFolderDialog(string aTitle, string aDefaultPathAndFile);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_colorChooser(string aTitle, string aDefaultHexRGB, byte[] aDefaultRGB, byte[] aoResultRGB);

    // windows only utf16
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tinyfd_notifyPopupW(string aTitle, string aMessage, string aIconType);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tinyfd_messageBoxW(string aTitle, string aMessage, string aDialogTyle, string aIconType, int aDefaultButton);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    public static extern string tinyfd_inputBoxW(string aTitle, string aMessage, string aDefaultInput);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    public static extern string tinyfd_saveFileDialogW(string aTitle, string aDefaultPathAndFile, int aNumOfFilterPatterns, string[] aFilterPatterns, string aSingleFilterDescription);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    public static extern string tinyfd_openFileDialogW(string aTitle, string aDefaultPathAndFile, int aNumOfFilterPatterns, string[] aFilterPatterns, string aSingleFilterDescription, int aAllowMultipleSelects);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    public static extern string tinyfd_selectFolderDialogW(string aTitle, string aDefaultPathAndFile);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    public static extern string tinyfd_colorChooserW(string aTitle, string aDefaultHexRGB, byte[] aDefaultRGB, byte[] aoResultRGB);
}

namespace ConsoleApplication1
{
    class tinyfiledialogsTest
    {
        private static string stringFromChar(IntPtr ptr)
        {
            return System.Runtime.InteropServices.Marshal.PtrToStringAnsi(ptr);
        }

        static void Main(string[] args)
        {
            // if you want UTF8 on windows (by default windows char is MBCS)
            //tinyfd.tinyfd_setWinUtf8(); // commented because you probably don't want to change it
                                          // (unless you are sure your project is expecting UTF-8)

            // cross platform utf8 (or MBCS on windows)
            IntPtr lTheInputText = tinyfd.tinyfd_inputBox("input box", "gimme a string", "A text to input");
            string lTheInputString = stringFromChar(lTheInputText);

            // cross platform utf8 (or MBCS on windows)
            int lala = tinyfd.tinyfd_messageBox("a message box char", lTheInputString, "ok", "warning", 1);

            // windows only utf16
            int lili = tinyfd.tinyfd_messageBoxW("a message box wchar_t", lTheInputString, "ok", "info", 1);

            // notify popup
            tinyfd.tinyfd_notifyPopup("there is no error (even if it is an error icon)", lTheInputString, "error");

            tinyfd.tinyfd_beep();
        }
    }
}
