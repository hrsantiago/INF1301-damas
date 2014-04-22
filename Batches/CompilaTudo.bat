@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

cd..\ferramnt

del ..\produto\*.err
del ..\produto\*.obj
del ..\produto\TesteLista.exe
del ..\produto\TESTEPECA.exe
del ..\produto\TESTETABULEIRO.exe

nmake /F..\composicao\testelista.make 
nmake /F..\composicao\TESTEPECA.make 
nmake /F..\composicao\TESTETABULEIRO.make 


copy  ..\produto\*.err  ..\produto\tudo.err

notepad ..\produto\tudo.err

popd
