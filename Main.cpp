
# include <Siv3D.hpp> // OpenSiv3D v0.4.3


void Main()
{
    Size canvasSize(600,600);
    double thickness = 8;
    Color penColor = Palette::Black;
    Color nijiColor = HSV(0, 1.0, 1.0, 1.0);
    double nijiH = 0;
    Image image(canvasSize, Palette::White);
    Image Undo(canvasSize, Palette::White);
    double Red = 0;
    double Blue = 0;
    double Green = 0;
    int32 type = 0;
    Rect rectDraw;
    Polygon Arrow;
    
    DynamicTexture texture(image);
    
    while (System::Update())
	{
        //プレビュー
        Rect(650,200, 100, 100).draw(penColor);
        Circle(700, 410, thickness/2).draw(penColor);
        //描画モード
        if(SimpleGUI::Button(U"●", Vec2(600,450),60)){
            type = 0;
        }else if(SimpleGUI::Button(U"■", Vec2(660,450),60)){
            type = 1;
        }else if(SimpleGUI::Button(U"↑", Vec2(720,450),60)){
            type = 2;
        }else if(SimpleGUI::Button(U"🌈", Vec2(600,500),60)){
            type = 3;
        }
        //描画する
        if(type==0 && MouseL.pressed()){
            const Point from = MouseL.down() ? Cursor::Pos() : Cursor::PreviousPos();
            
            const Point to = Cursor::Pos();
            
            Line(from, to).overwrite(image, thickness, penColor);
            
            texture.fill(image);
        }
        Point from1,to1;
        if(type == 1 && MouseL.down()){
            from1 = Cursor::Pos();
            
        }else if(type == 1 && MouseL.pressed()){
            to1 = Cursor::Pos();
            
        }else if(type == 1 && MouseL.up()){
            rectDraw = Rect(from1,to1-from1).draw(penColor);
            rectDraw.overwrite(image, penColor);
            texture.fill(image);
        }
        Point from2,to2;
        if(type == 2 && MouseL.down()){
            from2 = Cursor::Pos();
        }else if(type == 2 && MouseL.pressed()){
            to2 = Cursor::Pos();
        }else if(type == 2 && MouseL.up()){
            Arrow = Shape2D::Arrow(from2, to2, thickness, Vec2(thickness*2, thickness*3)).draw(penColor);
            Arrow.overwrite(image, penColor);
            texture.fill(image);
        }
        
        if(type == 3 && MouseL.pressed()){
            const Point from = MouseL.down() ? Cursor::Pos() : Cursor::PreviousPos();
            
            const Point to = Cursor::Pos();
            
            Line(from, to).overwrite(image, thickness, nijiColor);
            
            nijiH += 2;
            nijiColor = HSV(nijiH, 1.0, 1.0, 1.0);
            
            texture.fill(image);
        }
        
        if(SimpleGUI::Button(U"全消し", Vec2(640,40),120)){
            image.fill(Palette::White);
            texture.fill(image);
        }
        //色変更
        if(SimpleGUI::SliderAt(U"R", Red, 255.0, 0.0, Vec2(700, 100), 80, 120)){
            penColor = ColorF(Red/255,Green/255,Blue/255);
        };
        if(SimpleGUI::SliderAt(U"G", Green, 255.0, 0.0, Vec2(700, 130), 80, 120)){
            penColor = ColorF(Red/255,Green/255,Blue/255);
        };
        if(SimpleGUI::SliderAt(U"B", Blue, 255.0, 0.0, Vec2(700, 160), 80, 120)){
            penColor = ColorF(Red/255,Green/255,Blue/255);
        };
        
        if(SimpleGUI::SliderAt(U"太さ", thickness, 1, 200, Vec2(700, 320), 80, 120)){
            penColor = ColorF(Red/255,Green/255,Blue/255);
        };
        texture.draw();
        
    }
    
}



