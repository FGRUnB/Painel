# Painel

O painel de telemetria é uma ferramenta crucial para monitorar e otimizar o desempenho de um carro de Fórmula SAE Elétrico. Ele oferece dados em tempo real sobre o estado do veículo, permitindo que a equipe tenha controle e acesso a informações vitais sobre o funcionamento do carro, tanto durante testes quanto em competições. A criação de um sistema de telemetria usando o Qt para desenvolver a interface gráfica, junto com C++, Arduino, e Raspberry Pi, oferece uma solução robusta e eficiente para monitoramento e análise dos dados. A seguir, explico as principais razões para sua importância:

## 1. Monitoramento em Tempo Real
O painel de telemetria fornece dados em tempo real sobre diversos parâmetros do carro, como:

- **Temperatura das baterias:** Monitoramento crítico para garantir que o sistema não superaqueça.
- **Corrente e tensão:** Ajuda a evitar falhas elétricas e a entender como a energia está sendo utilizada.
- **Nível de carga da bateria:** Essencial para saber a autonomia do veículo durante a corrida.
- **Velocidade e aceleração:** Indicadores de desempenho dinâmico.
- **Status dos motores:** Permite identificar possíveis falhas ou quedas de eficiência nos motores elétricos.
Com essas informações, a equipe pode tomar decisões rápidas sobre ajustes durante a competição ou durante os treinos.

## 2. Diagnóstico e Prevenção de Falhas
Um sistema de telemetria bem desenvolvido, utilizando sensores conectados ao Arduino para a coleta de dados e processamento via Raspberry Pi, pode identificar problemas em potencial antes que eles causem falhas. Por exemplo, se um aumento anormal na temperatura da bateria for detectado, o sistema pode alertar a equipe, permitindo ações preventivas para evitar danos graves ao carro.

Além disso, a análise dos dados históricos pode ajudar a identificar padrões de desempenho que podem antecipar falhas, permitindo manutenções preventivas.

## 3. Otimização do Desempenho
Com o painel de telemetria, é possível ajustar o comportamento do carro de maneira mais precisa. A interface desenvolvida em Qt com C++ oferece uma plataforma amigável e visual para que a equipe analise os dados e faça ajustes no sistema do veículo, como:

- Alterar o mapeamento do acelerador.
- Ajustar os limites de corrente e potência fornecida pelos motores.
- Modificar os parâmetros de controle de tração.
- Esses ajustes podem ser feitos de acordo com o comportamento do carro em diferentes testes, como aceleração, skidpad, ou autocross, maximizando o desempenho.

## 4. Desenvolvimento com Qt, C++, Arduino e Raspberry Pi
- **Qt e C++:** Usar o Qt para desenvolver a interface gráfica do painel de telemetria permite criar uma interface interativa e customizável. O Qt oferece flexibilidade para desenhar gráficos em tempo real, exibir alertas, e organizar os dados de maneira clara e visual. O uso de C++ assegura eficiência e alto desempenho na integração com os hardwares e no processamento dos dados recebidos.

- **Arduino:** O Arduino é utilizado para capturar dados de sensores e atuadores no carro, como medições de temperatura, velocidade, corrente e tensão. Ele é ideal para essa tarefa devido à sua simplicidade e capacidade de trabalhar com uma ampla gama de sensores e protocolos de comunicação.

- **Raspberry Pi:** O Raspberry Pi atua como o processador central do sistema de telemetria. Ele pode coletar os dados do Arduino e transmitir para o painel desenvolvido em Qt, além de processar dados mais complexos, armazenar logs, e realizar cálculos para diagnósticos mais precisos.

## 6. Tomada de Decisões Baseadas em Dados
Com os dados oferecidos pela telemetria, a equipe pode tomar decisões estratégicas baseadas em informações objetivas. Isso pode significar ajustar a estratégia de corrida ou detectar a necessidade de substituição de componentes durante o evento. Sem um sistema de telemetria, muitas dessas decisões seriam baseadas em suposições, o que poderia comprometer o desempenho e a segurança do carro.
