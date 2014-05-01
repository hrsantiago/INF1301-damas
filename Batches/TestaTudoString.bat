@ECHO OFF
REM executa os testes de listaInt, peca e tabuleiro

cls

del ..\scripts\estatisticasString.estat

..\produto\TESTELISTA		/s..\scripts\TesteListastring	/l..\produto\TesteListaString	/a..\scripts\estatisticasString
..\produto\TESTEPECA  		/s..\scripts\Testepeca    	/l..\produto\TestePeca  	/a..\scripts\estatisticasString
..\produto\TESTETABULEIRO  	/s..\scripts\Testetabuleiro	/l..\produto\TesteTabuleiro   	/a..\scripts\estatisticasString

..\ferramnt\exbestat /e..\scripts\estatisticasString
