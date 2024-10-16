Updated: 

I solved my curiosity and worry.

I had to use FSlateBrush as the brush for the strike line. I saw that after my change from the FSlateBorderBrush to the FSlateBrush, this phenomenon does not appear anymore. (I'm ashamed.)

I'll update the code for the record for anyone else who may experience something similar to mine. (Maybe me of the future?) The part where this is happening is commented out. 

If you modify the commented part in "Plugins/TextBlockTest/Source/TextBlockTest/Private/TextBlockTest.cpp" in the code, you can see this phenomenon.

![Screenshot](https://github.com/hyaniner/UnrealSTextBlockBrokenWithStrikeBrush/blob/main/Screenshots/after.png)

---

Engine Ver: 5.4.4

You can see this in the menu, Window->TextBlockTest.

video: https://www.youtube.com/watch?v=o-BZwVsFmMs

When I set the "Editor/Slate/Old/Border.PNG" as the strike brush to STextBlock, this happens. Yes, I know that the purpose of that file is not like that. But I was worried about what I experience in the future like this. So I uploaded this. 

In my working project, This happened randomly. In my working project, whether this phenomenon will occur or not seemed determined when the editor is run, in my guess. Once this phenomenon occurs, it persists until the editor is closed. If I just close and open a window or tab that has this phenomenon, it still exists. 

This phenomenon disappears if I remove the STextBlock with the strike brush from the code through hot reload, and close and open again the window or tab that had STextBlock (to remake slate). But, after that, if I add STextBlock again with the strike brush through hot reload, close, and open that window or tab again, this phenomenon happens again.

![Screenshot](https://github.com/hyaniner/UnrealSTextBlockBrokenWithStrikeBrush/blob/main/Screenshots/Clipboard_10-16-2024_012.png)


