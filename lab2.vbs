Dim s
do
    WScript.StdOut.WriteLine "Menu:"
    WScript.StdOut.WriteLine "1. Information about autor"
    WScript.StdOut.WriteLine "2. Archiving of the specified folder"
    WScript.StdOut.WriteLine "3. Saving a list of files in a specified folder in a text file."
    WScript.StdOut.WriteLine "4. Exit"
    WScript.StdOut.Write "Choose paragraph of menu (1-4):"
    s = WScript.StdIn.ReadLine
    Set WshShell = WScript.CreateObject("WScript.Shell")

    if (s="1") Then
        WScript.StdOut.WriteLine " I'm Shyrokin Daniil, student of the group ITP-11"	
    elseif(s="2") Then
		WScript.StdOut.WriteLine "way to folder"
		InputFolder = WScript.StdIn.ReadLine
		WScript.StdOut.WriteLine "way rar folder"
		OutputFolder = WScript.StdIn.ReadLine
     	InputFolder = objArgs(0) ' Путь какую папку архивировать =====================|
		OutputFolder = objArgs(1) ' Путь куда архивировать ===========================|
		ZipFile = OutputFolder & Date & "_test.zip" ' Как назвать ===============|

		CreateObject("Scripting.FileSystemObject").CreateTextFile(ZipFile, True).Write "PK" & Chr(5) & Chr(6) & String(18, vbNullChar)
		Set objShell = CreateObject("Shell.Application")
		Set source = objShell.NameSpace(InputFolder).Items
			objShell.NameSpace(ZipFile).CopyHere(source)

		Do Until objShell.NameSpace(ZipFile).Items.Count = objShell.NameSpace(InputFolder).Items.Count
		   WScript.Sleep 500 ' Arbitrary polling delay
		Loop
		
        'Code=WshShell.Run("%COMSPEC% /c archive.cmd >"+way ,0,true) 

    elseif(s="3") Then

		sPath = inputbox("Enter way to folder: ") ' Путь к папке ====================|
		set oFSO = CreateObject("Scripting.FileSystemObject") 

		if not (oFSO.FolderExists(sPath)) then msgbox "invalid way to folder!": WScript.Quit 1 

		cur = oFSO.GetParentFolderName(WScript.ScriptFullName) 
		set oTStream = oFSO.CreateTextFile(cur & "\files.txt", true) 

		for each oFile in oFSO.GetFolder(sPath).Files 
	    oTStream.WriteLine oFile.Name 
		WScript.Echo oFile.Name 
		next 
		oTStream.Close 
		
    end if
loop until (s="4")

