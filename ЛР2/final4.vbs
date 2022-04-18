' ************************************************
' Имя: саша помин
' Язык: VBScript
'*************************************************
Dim FSO, FileName, F, s, oFSO, Folder, objFSO, Txtfile, FoldSize, outFile, x, namefrom, nameto, name
Do
    WScript.StdOut.WriteLine "Menu:"
    WScript.StdOut.WriteLine "----------------------------"
    WScript.StdOut.WriteLine "1. Author's info"
    WScript.StdOut.WriteLine "2. Transferring files from a specified location to a specified"
    WScript.StdOut.WriteLine "3. Saving in notepad the creation date and size of the specified folder"
    WScript.StdOut.WriteLine "4. Exit"
    WScript.StdOut.WriteLine "Select a menu item:"
    s = WScript.StdIn.ReadLine

    Set WshShell = WScript.CreateObject("WScript.Shell")
    if (s="1") Then
    WScript.StdOut.WriteLine " "
    WScript.StdOut.WriteLine " "
    WScript.StdOut.WriteLine "Rozhina A., ITP-11"
    WScript.StdOut.WriteLine " "
    WScript.StdOut.WriteLine " "

    elseif (s="2") Then
        WScript.StdOut.WriteLine " "
        WScript.StdOut.WriteLine " "
        WScript.StdOut.WriteLine "From (the path to the file):"
        namefrom = WScript.StdIn.ReadLine
        WScript.StdOut.WriteLine "To (the path to the folder):"
        nameto = WScript.StdIn.ReadLine
        Set objFso = CreateObject("Scripting.FileSystemObject")
        If objFso.FileExists(namefrom) Then
            If objFso.FolderExists(nameto) Then
                objFso.MoveFile namefrom, nameto
                WScript.StdOut.WriteLine "File transfer completed successfully"
                WScript.StdOut.WriteLine " "
                WScript.StdOut.WriteLine " "
                Set objFso = Nothing
            Else
                WScript.StdOut.WriteLine "File transfer didn't complete successfully"
            End If
        Else 
            WScript.StdOut.WriteLine "File transfer didn't complete successfully"
        End If

    elseif (s="3") Then
        WScript.StdOut.WriteLine " "
        WScript.StdOut.WriteLine " "
        Set oFSO = CreateObject("Scripting.FileSystemObject")
        WScript.StdOut.WriteLine "Enter the path to the folder:"
        name = WScript.StdIn.ReadLine
        If oFSO.FolderExists(name) Then
            Set Folder = oFSO.GetFolder(name)
            Set objFSO = CreateObject("Scripting.FileSystemObject")
            outFile = "E:\test1\3.txt"
            Set Txtfile = objFSO.CreateTextFile(outFile, True)
            x = x & "Date of the creation: " & Folder.DateCreated & vbCrLf
            FoldSize = Folder.Size/1024
            x = x & "Size: " & FoldSize & " Kb" & VbCrLf
            Txtfile.Write x & vbCrLf
            Txtfile.Close
            WScript.StdOut.WriteLine "File was created"
            WScript.StdOut.WriteLine "Watch here: E:\test1\3.txt"
            WScript.StdOut.WriteLine " "
            WScript.StdOut.WriteLine " "
        Else 
            WScript.StdOut.WriteLine "File wasn't created"
        End If
    End If

Loop Until s = "4"