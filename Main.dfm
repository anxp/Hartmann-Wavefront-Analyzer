object Form1: TForm1
  Left = 285
  Top = 69
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Hartmann Wavefront Analyzer - Computer Model (Ver. 2.0)'
  ClientHeight = 608
  ClientWidth = 446
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 1
    Top = 2
    Width = 443
    Height = 585
    BevelInner = bvLowered
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 6
      Top = 3
      Width = 432
      Height = 266
      Caption = ' Wavefront properties '
      Color = clBtnFace
      ParentColor = False
      TabOrder = 0
      object Label12: TLabel
        Left = 7
        Top = 194
        Width = 323
        Height = 13
        Caption = 
          'Supported functions: SIN(), COS(), TG(), ABS(), EXP(), SQRT(), L' +
          'N();'
        Color = clBtnFace
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clMaroon
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentColor = False
        ParentFont = False
      end
      object Label13: TLabel
        Left = 7
        Top = 211
        Width = 164
        Height = 13
        Caption = 'Supported operations: (, ), *, /, +, -;'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clMaroon
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label14: TLabel
        Left = 7
        Top = 228
        Width = 313
        Height = 13
        Caption = 
          'Note! Operation ^ (involution) is not supported and will not sup' +
          'port;'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clMaroon
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label15: TLabel
        Left = 7
        Top = 245
        Width = 386
        Height = 13
        Caption = 
          'Use these functions and operations to determine Wavefront shape ' +
          'and Amplitude.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clMaroon
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object GroupBox3: TGroupBox
        Left = 6
        Top = 15
        Width = 420
        Height = 125
        Caption = ' Wavefront shape '
        TabOrder = 0
        object Label1: TLabel
          Left = 13
          Top = 18
          Width = 45
          Height = 13
          Caption = 'Z(X, Y) = '
        end
        object Edit1: TEdit
          Left = 62
          Top = 15
          Width = 220
          Height = 21
          MaxLength = 199
          TabOrder = 0
          Text = '1'
        end
        object RadioButton1: TRadioButton
          Left = 290
          Top = 17
          Width = 41
          Height = 17
          Caption = 'mm'
          TabOrder = 1
          OnClick = RadioButton1Click
        end
        object RadioButton2: TRadioButton
          Left = 331
          Top = 17
          Width = 38
          Height = 17
          Caption = 'rad'
          Checked = True
          TabOrder = 2
          TabStop = True
          OnClick = RadioButton2Click
        end
        object GroupBox10: TGroupBox
          Left = 6
          Top = 40
          Width = 408
          Height = 78
          Caption = ' Normalization '
          TabOrder = 3
          object Label11: TLabel
            Left = 28
            Top = 32
            Width = 196
            Height = 13
            Caption = '(X=X/Ro; Y=Y/Ro; Ro=min(Xmax; Ymax))'
          end
          object RadioButton7: TRadioButton
            Left = 9
            Top = 16
            Width = 264
            Height = 17
            Caption = 'Normalize X and Y coordinates to sensor'#39's aperture'
            Checked = True
            TabOrder = 0
            TabStop = True
            OnClick = RadioButton7Click
          end
          object RadioButton8: TRadioButton
            Left = 9
            Top = 50
            Width = 317
            Height = 17
            Caption = 'Normalize X and Y coordinates to user-defined radius Ro(mm)='
            TabOrder = 1
            OnClick = RadioButton8Click
          end
          object Edit12: TEdit
            Left = 326
            Top = 48
            Width = 74
            Height = 21
            Enabled = False
            TabOrder = 2
            Text = '1'
          end
        end
      end
      object GroupBox4: TGroupBox
        Left = 6
        Top = 143
        Width = 420
        Height = 47
        Caption = ' Amplitude '
        TabOrder = 1
        object Label2: TLabel
          Left = 13
          Top = 18
          Width = 45
          Height = 13
          Caption = 'A(X, Y) = '
        end
        object Edit2: TEdit
          Left = 62
          Top = 15
          Width = 220
          Height = 21
          MaxLength = 199
          TabOrder = 0
          Text = '1'
        end
      end
    end
    object GroupBox2: TGroupBox
      Left = 6
      Top = 272
      Width = 432
      Height = 164
      Caption = ' Wavefront sensor'#39's parameters '
      TabOrder = 1
      object Label4: TLabel
        Left = 8
        Top = 87
        Width = 66
        Height = 13
        Caption = 'Focus (mm) = '
      end
      object Label5: TLabel
        Left = 8
        Top = 112
        Width = 104
        Height = 13
        Caption = 'Lens'#39' aperture (mm) = '
      end
      object Label6: TLabel
        Left = 194
        Top = 88
        Width = 128
        Height = 13
        Caption = 'Number of lens by X axis = '
      end
      object Label7: TLabel
        Left = 194
        Top = 113
        Width = 128
        Height = 13
        Caption = 'Number of lens by Y axis = '
      end
      object Label8: TLabel
        Left = 194
        Top = 138
        Width = 166
        Height = 13
        Caption = 'Size of pixel at focal plane (mcm) = '
      end
      object Label9: TLabel
        Left = 8
        Top = 137
        Width = 93
        Height = 13
        Caption = 'Wavelength (nm) = '
      end
      object GroupBox5: TGroupBox
        Left = 6
        Top = 15
        Width = 88
        Height = 62
        Caption = ' Type of lens '
        TabOrder = 0
        object RadioButton3: TRadioButton
          Left = 9
          Top = 18
          Width = 71
          Height = 17
          Caption = 'Refraction'
          Checked = True
          TabOrder = 0
          TabStop = True
          OnClick = RadioButton3Click
        end
        object RadioButton4: TRadioButton
          Left = 9
          Top = 39
          Width = 67
          Height = 17
          Caption = 'Difraction'
          TabOrder = 1
          OnClick = RadioButton4Click
        end
      end
      object GroupBox6: TGroupBox
        Left = 98
        Top = 15
        Width = 328
        Height = 62
        Caption = 
          ' Axial angle between obj and ref wavefronts (difraction lens onl' +
          'y) '
        TabOrder = 1
        object Label3: TLabel
          Left = 13
          Top = 29
          Width = 38
          Height = 13
          Caption = 'alpha = '
        end
        object Edit3: TEdit
          Left = 54
          Top = 26
          Width = 68
          Height = 21
          TabOrder = 0
          Text = '0.01'
        end
        object RadioButton5: TRadioButton
          Left = 129
          Top = 27
          Width = 58
          Height = 17
          Caption = 'radians'
          Checked = True
          TabOrder = 1
          TabStop = True
        end
        object RadioButton6: TRadioButton
          Left = 201
          Top = 27
          Width = 60
          Height = 17
          Caption = 'degrees'
          TabOrder = 2
        end
      end
      object Edit4: TEdit
        Left = 79
        Top = 84
        Width = 93
        Height = 21
        TabOrder = 2
        Text = '53'
      end
      object Edit5: TEdit
        Left = 114
        Top = 109
        Width = 58
        Height = 21
        TabOrder = 3
        Text = '0.4'
      end
      object Edit6: TEdit
        Left = 325
        Top = 84
        Width = 84
        Height = 21
        TabOrder = 4
        Text = '4'
      end
      object Edit7: TEdit
        Left = 325
        Top = 109
        Width = 84
        Height = 21
        TabOrder = 5
        Text = '4'
      end
      object Edit8: TEdit
        Left = 363
        Top = 134
        Width = 60
        Height = 21
        TabOrder = 6
        Text = '9.3'
      end
      object Edit9: TEdit
        Left = 103
        Top = 134
        Width = 69
        Height = 21
        TabOrder = 7
        Text = '630'
      end
      object UpDown1: TUpDown
        Left = 409
        Top = 84
        Width = 16
        Height = 21
        Associate = Edit6
        Min = 1
        Position = 4
        TabOrder = 8
        Wrap = False
      end
      object UpDown2: TUpDown
        Left = 409
        Top = 109
        Width = 16
        Height = 21
        Associate = Edit7
        Min = 1
        Position = 4
        TabOrder = 9
        Wrap = False
      end
    end
    object GroupBox7: TGroupBox
      Left = 6
      Top = 442
      Width = 247
      Height = 68
      Caption = ' Calculations options '
      TabOrder = 2
      object Label10: TLabel
        Left = 6
        Top = 17
        Width = 163
        Height = 13
        Caption = 'Number of points by lens by axis = '
      end
      object Edit10: TEdit
        Left = 170
        Top = 14
        Width = 51
        Height = 21
        TabOrder = 0
        Text = '128'
      end
      object Button1: TButton
        Left = 221
        Top = 14
        Width = 19
        Height = 10
        Caption = '+'
        TabOrder = 1
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 221
        Top = 25
        Width = 19
        Height = 10
        Caption = '-'
        TabOrder = 2
        OnClick = Button2Click
      end
      object CheckBox2: TCheckBox
        Left = 6
        Top = 43
        Width = 238
        Height = 17
        Caption = 'Adjust picture to Shack-Hartmann Sensor size'
        TabOrder = 3
      end
    end
    object GroupBox9: TGroupBox
      Left = 6
      Top = 510
      Width = 432
      Height = 46
      Caption = ' Start calculations '
      TabOrder = 3
      object Button3: TButton
        Left = 7
        Top = 14
        Width = 104
        Height = 24
        Caption = 'START'
        TabOrder = 0
        OnClick = Button3Click
      end
      object Button4: TButton
        Left = 215
        Top = 14
        Width = 104
        Height = 24
        Caption = 'STOP'
        Enabled = False
        TabOrder = 1
        OnClick = Button4Click
      end
      object Button5: TButton
        Left = 319
        Top = 14
        Width = 104
        Height = 24
        Caption = 'SAVE_AND_EXIT'
        TabOrder = 2
        OnClick = Button5Click
      end
      object Button6: TButton
        Left = 111
        Top = 14
        Width = 104
        Height = 24
        Caption = 'PAUSE'
        TabOrder = 3
        OnClick = Button6Click
      end
    end
    object ProgressBar1: TProgressBar
      Left = 6
      Top = 559
      Width = 432
      Height = 20
      Min = 0
      Max = 200
      TabOrder = 4
    end
    object GroupBox8: TGroupBox
      Left = 258
      Top = 442
      Width = 180
      Height = 68
      Caption = ' Input name for bitmap: '
      TabOrder = 5
      object Edit11: TEdit
        Left = 9
        Top = 27
        Width = 159
        Height = 21
        TabOrder = 0
        Text = 'test.bmp'
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 589
    Width = 446
    Height = 19
    Panels = <
      item
        Text = 'Status: Edit scheme'
        Width = 200
      end
      item
        Text = 'Elapsed time (sec) : ??????'
        Width = 150
      end>
    SimplePanel = False
  end
end
