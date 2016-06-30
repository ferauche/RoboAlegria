O Webservice é divido em duas partes principais:  
  
* Webservice Backend  
* Interface Frontend  
  
  
##Descrição##  
  
O Webservice deve rodar em um servidor HTTP. Onde será acessado (por IP) pelo app android.
O Servidor deve armazenar um arquivo .txt e um arquivo de áudio, que serão escritos pela Interface Frontend, esses arquios serão lidos pelo app android por endereços URL específicos.

Pela Interface Frontend o controlador poderá escolher as expressões (olhos e boca) e movimentação dos braços para o robô. Quando o controlador escolhe alguma ação para o robô, o Backend escreve no arquivo .txt o código referente a ação, o app android vai ler o arquivo .txt e enviar o comano para o robô executar.  
  
O controlador tambem poderá fazer gravação de áudio que será salva em um arquivo no servidor. Quando um áudio é gravado, o Backend salva o arquivo (formato de áudio à definir), escreve no arquivo .txt, para o app android ler o arquivo de áudio e reproduzi lo.

Na Interface Frontend o controlador tambem poderá visualizar o vídeo e ouvir o áudio enviados pelo app android. O Webservice deverá acessar um endereço URL específico fornecido pelo app android para acessar o vídeo e áudio.

A Interface Frontend terá alguns campos de textos, para o controlador fazer anotações sobre a criança.
  
A Interface Frontend tem como base a imagem abaixo.  
![alt tag](https://github.com/helam01/RoboAlegria/blob/webservice/images/interface_web.jpg)