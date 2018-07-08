object Form2: TForm2
  Left = 297
  Top = 340
  BorderStyle = bsDialog
  Caption = 'Wait...'
  ClientHeight = 67
  ClientWidth = 338
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  Scaled = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 1
    Top = 3
    Width = 336
    Height = 63
    BevelInner = bvLowered
    TabOrder = 0
    object Label1: TLabel
      Left = 91
      Top = 24
      Width = 166
      Height = 13
      Caption = 'Please, wait for process termination'
    end
  end
end
