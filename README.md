# Loja de Discos

## Descrição do Projeto

O projeto **"Loja de Discos"** é uma aplicação desenvolvida para o trabalho da disciplina de AEDS II, com o objetivo de gerenciar eficientemente uma loja especializada na venda de discos de música. A aplicação facilita o cadastro, organização, consulta e gerenciamento de discos, clientes e funcionários, além de possibilitar o processamento de vendas e o acompanhamento do estoque.

## Objetivo

O principal objetivo da aplicação é proporcionar uma gestão eficiente dos seguintes aspectos:
- **Cadastro e organização de discos**: Permitir a inclusão, atualização e remoção de discos do catálogo da loja.
- **Gerenciamento de clientes**: Registrar e atualizar informações sobre os clientes, bem como manter o histórico de suas compras.
- **Administração de funcionários**: Manter dados dos funcionários responsáveis pelas operações da loja.
- **Processamento de vendas**: Registrar as vendas realizadas, atualizar o estoque e gerar relatórios de desempenho.

## Entidades

1. **Disco**
   - `id`: Identificador único do disco.
   - `titulo`: Título do disco.
   - `artista`: Artista responsável pelo disco.
   - `genero`: Gênero musical do disco.
   - `ano`: Ano de lançamento.
   - `preco`: Preço do disco.
   - `estoque`: Quantidade disponível em estoque.
   
2. **Cliente**
   - `id`: Identificador único do cliente.
   - `nome`: Nome completo do cliente.
   - `cpf`: CPF do cliente.
   - `telefone`: Número de telefone do cliente.
   - `historico_compras`: Lista de compras realizadas pelo cliente.

3. **Funcionário**
   - `id`: Identificador único do funcionário.
   - `nome`: Nome completo do funcionário.
   - `cpf`: CPF do funcionário.

4. **Compra**
   - `id`: Identificador único da compra.
   - `disco_id`: Identificador do disco comprado.
   - `id_cliente`: Id do cliente que realizou a compra.
   - `id_funcionario`: Identificador do funcionário que processou a compra.
   - `quantidade`: Quantidade comprada.
   - `valor_total`: Valor total da compra.
