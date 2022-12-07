
#include <WiFi.h>                         //biblioteca WiFi


// ============================================================================
// --- Mapeamento de Hardware ---
#define   led1   9    
#define   led2   11 
#define   led3   13
#define   led4   35
#define   led5   48
#define   led6   21               
#define   buzzer   16                    


// ============================================================================
// --- Constantes Auxialires ---
const char *ssid     = "Inteli-COLLEGE";  //atribuir nome da rede WiFi
const char *password = "QazWsx@123"; //atribuir senha da rede


// ============================================================================
// --- Objetos ---
WiFiServer server(80);                    //define a porta que o servidor irá utilizar
                                          //(normalmente utiliza-se a porta padrão 80)

// ============================================================================
// --- Protótipo das Funções ---
void relay_wifi();                       //função para gerar web server e controlar os relés
                                

// ============================================================================

void setup() 
{
  Serial.begin(115200);              
  pinMode(led1, OUTPUT);               
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(buzzer, OUTPUT);          

  Serial.println();                      //
  Serial.print("Conectando-se a ");      //
  Serial.println(ssid);                  //
  WiFi.begin(ssid, password);            //inicializa WiFi, passando o nome da rede e a senha

  while(WiFi.status() != WL_CONNECTED)   //aguarda conexão (WL_CONNECTED é uma constante que indica sucesso na conexão)
  {
    delay(741);                          //
    Serial.print(".");                   //vai imprimindo pontos até realizar a conexão...
  }

  Serial.println("");                    //mostra WiFi conectada
  Serial.println("WiFi conectada");      //
  Serial.println("Endereço de IP: ");    //
  Serial.println(WiFi.localIP());        //mostra o endereço IP

  server.begin();                        //inicializa o servidor web

}


// ============================================================================
// --- Loop Infinito ---
void loop() 
{


  while(WiFi.status() != WL_CONNECTED)   //aguarda conexão (WL_CONNECTED é uma constante que indica sucesso na conexão)
  {
    WiFi.begin(ssid, password);          //inicializa WiFi, passando o nome da rede e a senha
    Serial.print(".");                   //vai imprimindo pontos até realizar a conexão...

    delay(741);                          //741ms
  }
  
  relay_wifi();                                //chama função para controle dos relés por wifi


  
} //end loop


// ============================================================================
// --- relay_wifi ---
void relay_wifi()
{

  WiFiClient client = server.available();      //verifica se existe um cliente conectado com dados a serem transmitidos
  
  if(client)                                   //existe um cliente?
  {                                            //sim
    Serial.println("Novo Cliente Definido");   //informa por serial
    String currentLine = "";                   //string para armazenar a mensagem do cliente
    
    while(client.connected())                  //repete enquanto o cliente estiver conectado
    {
      
      if(client.available())                   //existem dados a serem lidos?
      {                                        //sim
        char c=client.read();                  //salva em c
        Serial.write(c);                       //mostra na Serial
        
        if(c=='\n')                            //é um caractere de nova linha?
        {                                      //sim
          if(currentLine.length()==0)          //a mensagem terminou?
          {                                    //sim
            //gera a página HTML
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h1>Quiz stranger things!!</h2><br>");
            client.print("<h2>Primeira pergunta para o jogador 1!!</h2><br>");
            client.print("<h2>Qual o verdadeiro nome da Eleven?</h2><br>");            
            client.print("<h2>A) <a href=\"/H1\">Onze</a></h2><br>");
            client.print("<h2>B) <a href=\"/H2\">Jane</a></h2><br>");
            client.print("<h2>C) <a href=\"/H1\">Julia</a></h2><br>");
            client.print("<h2>D) <a href=\"/H1\">Eleven</a></h2><br>");
            client.println();
            break;                             //encerra o laço
            
          } //end if currentLine.length
          
          else currentLine="";                 //senão, impede string de ficar com espaços em branco
        
        } //end if c
                  
        else if(c != '\r') currentLine += c;  //adicionamos o caractere como parte da mensagem, se diferene de retorno/nova linha

       //verifica para ligar ou desligar os relés
          if(currentLine.endsWith("GET /H1")){
            tone(buzzer, 1000);
            delay(1000); 
            noTone(buzzer);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Errado, o certo era Jane, vez do jogador 2, clique <a href=\"/H3\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;                 
          };
          if(currentLine.endsWith("GET /H2")){
            tone(buzzer, 1000);
            delay(1000); 
            noTone(buzzer);
            digitalWrite(led1, HIGH);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Voce acertou!!Vez do jogador 2, clique <a href=\"/H3\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break; 
          };

          if(currentLine.endsWith("GET /H3")){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Qual o vilao da 4 temporada?</h2><br>");
            client.print("<h2>A) <a href=\"/H4\">Demogorgon</a></h2><br>");
            client.print("<h2>B) <a href=\"/H4\">Devorador de mentes</a></h2><br>");
            client.print("<h2>C) <a href=\"/H4\">Demo cao</a></h2><br>");
            client.print("<h2>D) <a href=\"/H5\">Vecna</a></h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /H5")){
            tone(buzzer, 1000);
            delay(1000); 
            noTone(buzzer);
            digitalWrite(led4, HIGH);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Voce acertou!!Vez do jogador 1, clique <a href=\"/H6\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /H4")){
            tone(buzzer, 1000);
            delay(1000); 
            noTone(buzzer);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Errado, o certo era Vecna, vez do jogador 1, clique <a href=\"/H6\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /H6")){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Qual o nome da irma da Eleven?</h2><br>");
            client.print("<h2>A) <a href=\"/H7\">Kali</a></h2><br>");
            client.print("<h2>B) <a href=\"/H8\">Nancy</a></h2><br>");
            client.print("<h2>C) <a href=\"/H8\">Max</a></h2><br>");
            client.print("<h2>D) <a href=\"/H8\">Rachell</a></h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /H8")){
            tone(buzzer, 1000);
            delay(1000); 
            noTone(buzzer);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Errado, o certo era Kali, vez do jogador 2, clique <a href=\"/H9\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /H7")){
            tone(buzzer, 1000);
            delay(1000); 
            noTone(buzzer);
            digitalWrite(led2, HIGH);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Voce acertou!!Vez do jogador 2, clique <a href=\"/H9\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /H9")){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Qual e o namorado da Eleven?</h2><br>");
            client.print("<h2>A) <a href=\"/l1\">Mike</a></h2><br>");
            client.print("<h2>B) <a href=\"/l2\">Will</a></h2><br>");
            client.print("<h2>C) <a href=\"/l2\">Lucas</a></h2><br>");
            client.print("<h2>D) <a href=\"/l2\">Dustin</a></h2><br>");
            client.println();
            break;
          
          };


          if(currentLine.endsWith("GET /l1")){
            tone(buzzer, 1000);
            delay(1000); 
            noTone(buzzer);
            digitalWrite(led5, HIGH);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Voce acertou!!Vez do jogador 1, clique <a href=\"/l3\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };
          
          if(currentLine.endsWith("GET /l2")){
            tone(buzzer, 1000);
            delay(1000); 
            noTone(buzzer);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Errado, o certo era Mike, vez do jogador 1, clique <a href=\"/l3\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /l3")){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Quantas vitimas o vecna precisava para concluir seu plano?</h2><br>");
            client.print("<h2>A) <a href=\"/l4\">1</a></h2><br>");
            client.print("<h2>B) <a href=\"/l5\">4</a></h2><br>");
            client.print("<h2>C) <a href=\"/l4\">6</a></h2><br>");
            client.print("<h2>D) <a href=\"/l4\">10</a></h2><br>");
            client.println();
            break;
          
          };

          if(currentLine.endsWith("GET /l5")){
            tone(buzzer, 1000);
            delay(1000); 
            noTone(buzzer);
            digitalWrite(led3, HIGH);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Voce acertou!!Vez do jogador 2, clique <a href=\"/l6\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /l5")){
            tone(buzzer, 1000);
            delay(1000); 
            noTone(buzzer);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Voce Errou eram 4!!Vez do jogador 2, clique <a href=\"/l6\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /l6")){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Quem morreu na 1 temporada?</h2><br>");
            client.print("<h2>A) <a href=\"/l8\">Barbara</a></h2><br>");
            client.print("<h2>B) <a href=\"/l7\">Will</a></h2><br>");
            client.print("<h2>C) <a href=\"/l7\">Billy</a></h2><br>");
            client.print("<h2>D) <a href=\"/l7\">Petter</a></h2><br>");
            client.println();
            break;
          
          };

          if(currentLine.endsWith("GET /l8")){
            tone(buzzer, 1000);
            delay(1000); 
            noTone(buzzer);
            digitalWrite(led6, HIGH);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h1>Voce acertou!!Veja quem tem mais leds ligadas para saber quem ganhou!.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /l7")){
            tone(buzzer, 1000);
            delay(1000); 
            noTone(buzzer);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h1>Voce Errou era Barbara!!Veja quem tem mais leds ligadas para saber quem ganhou!</h2><br>");
            client.println();
            break;
          };
       
      } //end if client.available()
      
    } //end if while client.connected

    client.stop();                           //finaliza conexão
    Serial.println("Client Disconnected.");
    
  } //end if client  
  
  
} //end relay_wifi










/* ========================================================   
 
                                                              
======================================================== */
/* --- Final do Programa --- */