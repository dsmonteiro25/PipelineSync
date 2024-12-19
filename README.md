# <a name="_bexghtgkx7gb"></a>**README - Comunicação entre Processos com Pipes**
## <a name="_17qrdciorts"></a>**Autor: Daniel Santos Monteiro**
## <a name="_17qrdciorts"></a>**Descrição do Programa**
Este programa demonstra a comunicação entre dois processos (produtor e consumidor) utilizando **pipes bidirecionais** para garantir sincronização e troca de mensagens ordenada. O produtor envia mensagens sequenciais para o consumidor, e o consumidor processa cada mensagem antes de confirmar seu recebimento. A implementação evita problemas de desordem nas mensagens, comuns em versões mais simples que utilizam apenas um único pipe.
## <a name="_vjaac5j9rn5g"></a>**Funcionalidade**
- O **produtor** gera mensagens numeradas sequencialmente ("Mensagem número X") e as envia pelo pipe para o **consumidor**.
- O **consumidor** lê a mensagem, a processa, e retorna uma confirmação para o produtor por meio de outro pipe.
- O produtor aguarda a confirmação antes de enviar a próxima mensagem, garantindo sincronização completa.
## <a name="_ndjslwcyro5w"></a>**Estrutura do Código**
O código está organizado em três funções principais:

1. **produtor**: Responsável por enviar mensagens ao consumidor e aguardar confirmações.
1. **consumidor**: Lê as mensagens do produtor, processa, e envia uma confirmação de volta.
1. **main**: Configura os pipes bidirecionais, cria o processo filho (consumidor), e coordena as funções.
## <a name="_vwxtqq69k9c3"></a>**Problemas Encontrados na Versão Inicial**
### <a name="_30ezfno5fcpn"></a>**Versão com Apenas um Pipe**
Na versão inicial, apenas um pipe era utilizado para transmitir mensagens do produtor para o consumidor. Isso gerava os seguintes problemas:

1. **Mensagens fora de ordem**: Devido à concorrência entre os processos, o consumidor podia processar mensagens em um momento diferente do que o produtor esperava.
   1. Exemplo: O produtor enviava "Mensagem número 2" antes do consumidor processar "Mensagem número 1".
1. **Ausência de sincronização**: O produtor não tinha garantias de que o consumidor havia processado uma mensagem antes de enviar a próxima.

Esses problemas resultavam em uma comunicação desordenada, prejudicando a previsibilidade do sistema.
## <a name="_viz6b6irzfiz"></a>**Justificativa para o Uso de Dois Pipes**
Para solucionar os problemas, foi implementado um segundo pipe, criando uma comunicação bidirecional:

1. **Pipe 1**: Produtor envia mensagens ao consumidor.
1. **Pipe 2**: Consumidor envia confirmações ao produtor.

Essa abordagem oferece as seguintes vantagens:

- **Sincronização Garantida**: O produtor aguarda explicitamente a confirmação do consumidor antes de enviar a próxima mensagem.
- **Execução Ordenada**: Cada mensagem é processada na ordem em que foi enviada, eliminando problemas de concorrência.
- **Feedback Explícito**: O produtor sabe quando o consumidor processou cada mensagem.
## <a name="_zap052vzj4jn"></a>**Ambiente Implementado**
VirtualBox is 7.0.0
Linux Mint: Linux Mint version 21.2
Visual Studio Code is 1.80.0
## <a name="_wgezfgozvhw1"></a>**Exemplo de Saída**
Iniciando o processo consumidor...

Iniciando o processo produtor...

Produtor: enviando 'Mensagem número 1'

Consumidor: Mensagem número 1

Produtor: confirmação recebida: 'Recebido'

Produtor: enviando 'Mensagem número 2'

Consumidor: Mensagem número 2

Produtor: confirmação recebida: 'Recebido'

...

Processo produtor finalizado.

Processo consumidor finalizado.

## <a name="_tfd8y8832ty0"></a>**Conclusão**
A implementação com dois pipes garante comunicação confiável e ordenada entre os processos, resolvendo os problemas de concorrência e desordem encontrados na versão inicial. Esse modelo pode ser facilmente adaptado para sistemas mais complexos que necessitem de comunicação interprocessos robusta.

