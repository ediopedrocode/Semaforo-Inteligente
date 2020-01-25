# Projeto "Semáforo Inteligente"

Projeto apresentado como requisito da disciplina Técnicas de Programação, ministrada pelo professor Me. Patric Lacouth Silva, pelos discentes Édio Pedro Belo de Melo, Fabrício da Silva Leitão e Gabriel Diniz Gomes. 


# Manual do Usuário
## Vias de trecho semaforizado tipificadas no protótipo
A maquete simula duas ruas em cruzamento, ambas funcionando em sentido únicos em duas faixas. As vias são principal e secundária.
#### 1) Via principal
Representa uma rua cujo tráfego de veículos é mais movimentado.
O semáforo relativo a essa via é normalmente aberto, devido ao elevado fluxo de veículos. 
#### 2) Via secundária
Essa é a rua cujo tráfego de veículos é menos movimentado.
O semáforo relativo a essa via é normalmente fechado, devido ao baixo fluxo de veículos. 
A **alteração de preferência da via 1 para a 2** ocorre quando são detectados veículos nesta, ocasionando a abertura do respectivo semáforo. 

## *Interface* QT *Creator* 
*Interface* de controle e monitoramento do sistema que simula um trecho de trânsito semaforizado. Esse programa é conectado ao microcontrolador por meio da porta serial, entrada/saída USB do computador.  

![enter image description here](https://github.com/ediopedrocode/Semaforo-Inteligente/blob/master/Imagens/WhatsApp%20Image%202020-01-25%20at%2010.52.40.jpeg?raw=true)


## Página *web*

Página *web* atrelada ao protótipo por intermédio de conexão Wireless. Operacionalidade:
**1) Informa** o número de veículos que trafegam pelas duas vias de dupla faixa e sentido único, que se cruzam, em tempo real;
**2) Controla** o estado de ambos os semáforos das vias, no que diz respeito ao estado de alerta, quando todos os sinais amarelos piscam, bem como a dar preferência de tráfego a pedestres.

![enter image description here](https://github.com/ediopedrocode/Semaforo-Inteligente/blob/master/Imagens/WhatsApp%20Image%202020-01-25%20at%2010.53.39.jpeg?raw=true)
