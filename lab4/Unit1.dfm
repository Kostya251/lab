object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Browser history editor'
  ClientHeight = 339
  ClientWidth = 592
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Hack'
  Font.Style = []
  Menu = MainMenu1
  Position = poDesigned
  OnClose = FormClose
  OnCreate = FormCreate
  TextHeight = 14
  object GridPanel1: TGridPanel
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 586
    Height = 333
    Align = alClient
    Caption = 'GridPanel1'
    ColumnCollection = <
      item
        Value = 14.573235819467120000
      end
      item
        Value = 85.426764180532890000
      end>
    ControlCollection = <
      item
        Column = 0
        Control = btnDelete
        Row = 1
      end
      item
        Column = 0
        ColumnSpan = 2
        Control = StatusBar1
        Row = 2
      end
      item
        Column = 0
        ColumnSpan = 2
        Control = VirtualStringTree
        Row = 0
      end
      item
        Column = 1
        Control = Button1
        Row = 1
      end>
    RowCollection = <
      item
        Value = 100.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 30.000000000000000000
      end
      item
        SizeStyle = ssAuto
      end>
    TabOrder = 0
    object btnDelete: TButton
      AlignWithMargins = True
      Left = 4
      Top = 286
      Width = 79
      Height = 24
      Align = alClient
      Caption = 'Delete row'
      Constraints.MaxHeight = 25
      Constraints.MaxWidth = 80
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnDeleteClick
    end
    object StatusBar1: TStatusBar
      Left = 1
      Top = 313
      Width = 584
      Height = 19
      Align = alClient
      Panels = <
        item
          Width = 250
        end>
    end
    object VirtualStringTree: TVirtualStringTree
      Left = 1
      Top = 1
      Width = 584
      Height = 282
      Align = alClient
      ClipboardFormats.Strings = (
        'Plain text')
      Colors.BorderColor = 15987699
      Colors.DisabledColor = clGray
      Colors.DropMarkColor = 15385233
      Colors.DropTargetColor = 15385233
      Colors.DropTargetBorderColor = 15385233
      Colors.FocusedSelectionColor = 15385233
      Colors.FocusedSelectionBorderColor = 15385233
      Colors.GridLineColor = 15987699
      Colors.HeaderHotColor = clBlack
      Colors.HotColor = clBlack
      Colors.SelectionRectangleBlendColor = 15385233
      Colors.SelectionRectangleBorderColor = 15385233
      Colors.SelectionTextColor = clBlack
      Colors.TreeLineColor = 9471874
      Colors.UnfocusedColor = clGray
      Colors.UnfocusedSelectionColor = clWhite
      Colors.UnfocusedSelectionBorderColor = clWhite
      Header.AutoSizeIndex = 0
      Header.Options = [hoAutoResize, hoDblClickResize, hoDrag, hoShowSortGlyphs, hoVisible]
      TabOrder = 2
      TreeOptions.PaintOptions = [toShowButtons, toShowDropmark, toShowTreeLines, toThemeAware, toUseBlendedImages]
      TreeOptions.SelectionOptions = [toFullRowSelect, toMultiSelect]
      OnAddToSelection = VirtualStringTreeAddToSelection
      OnGetText = VirtualStringTreeGetText
      Touch.InteractiveGestures = [igPan, igPressAndTap]
      Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
      Columns = <
        item
          Position = 0
          Text = 'URL'
          Width = 460
        end
        item
          Position = 1
          Text = #1044#1072#1090#1072' '#1087#1086#1089#1077#1097#1077#1085#1080#1103
          Width = 120
        end>
    end
    object Button1: TButton
      AlignWithMargins = True
      Left = 89
      Top = 286
      Width = 84
      Height = 25
      Align = alLeft
      Caption = 'Clear table'
      Constraints.MaxHeight = 25
      Constraints.MaxWidth = 84
      Constraints.MinHeight = 25
      Constraints.MinWidth = 84
      TabOrder = 3
      OnClick = Button1Click
    end
  end
  object MainMenu1: TMainMenu
    Left = 208
    Top = 112
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
      object N2: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        OnClick = N2Click
      end
      object N3: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = N3Click
      end
    end
  end
  object OpenDialog1: TOpenDialog
    FileName = 'History'
    Left = 435
    Top = 291
  end
end
