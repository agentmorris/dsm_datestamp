# dsm_datestamp

Windows shell extension to add a date/time stamp to filenames, before the extension.  For example, I might right-click on a file named:

  hello.txt

...and select dsm_datestamp, and the file would be renamed to:

  hello.17.07.22.12.38.11.txt
  
...if I ran it at 12:38.11pm on July 22, 2017.

If you run it on a file that already looks like it's been datestamped, it will update the datestamp.  It can operate on multiple files.

This is useful for archiving backups and what not.

To install, move the .dll (the x86 or x64 version) to your system32 directory, and at the command line, run:

```
  cd c:\windows\system32
  regsvr32 dsm_datestamp_x86.dll
```

To uninstall:

```
  cd c:\windows\system32
  regsvr32 /u dsm_datestamp_x86.dll
```

Technically you can use whatever directory you like, but system32 is the most sensible place.


