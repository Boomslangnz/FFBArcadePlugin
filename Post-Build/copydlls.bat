cd %1 %2
for /D /r %%d in (.) do @xcopy *.dll "%%d\" /y
for /D /r %%d in (.) do @xcopy FFBPlugin.txt "%%d\" /y
del %1\*.dll
del %1\FFBPlugin.txt