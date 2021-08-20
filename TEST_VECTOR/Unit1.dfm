object Form1: TForm1
  Left = 0
  Top = 0
  Width = 935
  Height = 665
  AutoScroll = True
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 15
    Top = 439
    Width = 31
    Height = 13
    Caption = 'Label1'
  end
  object Image1: TImage
    Left = 111
    Top = 8
    Width = 786
    Height = 561
    Transparent = True
    OnMouseDown = Image1MouseDown
  end
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 97
    Height = 297
    Color = clSilver
    ParentBackground = False
    TabOrder = 0
    object SpeedButton1: TSpeedButton
      Left = 7
      Top = 11
      Width = 52
      Height = 52
      Caption = 'R'
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 7
      Top = 69
      Width = 52
      Height = 52
      Caption = 'C'
      OnClick = SpeedButton2Click
    end
    object SpeedButton3: TSpeedButton
      Left = 7
      Top = 127
      Width = 52
      Height = 52
      Caption = 'D'
      OnClick = SpeedButton3Click
    end
    object Shape1: TShape
      Left = 15
      Top = 232
      Width = 57
      Height = 49
      Shape = stCircle
    end
  end
  object Memo1: TMemo
    Left = 8
    Top = 311
    Width = 97
    Height = 122
    TabOrder = 1
  end
end
