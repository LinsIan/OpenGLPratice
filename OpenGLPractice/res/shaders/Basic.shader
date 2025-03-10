// shader說明：宣告position，透過id0取得postion Attrib，並宣告成vector4，不足的資料會自動補

// 自定義的語法，用來讀檔時確認是哪種shader
#shader vertex
#version 330 core
        
layout(location = 0) in vec4 position; //in代表輸入變數，會抓該頂點id=0的attrib資料

void main()
{
    gl_Position = position; // gl_Position是內建的，代表頂點的位置
}

#shader fragment
#version 330 core
        
//定義一個輸出變量，然後綁定到framebuffer的第一個顏色緩衝區（也就是最終呈現在螢幕上的主要顏色buffer)
layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
    color = u_Color;
}
