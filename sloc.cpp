#include <iostream>
#include <dirent.h>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
/***
 * @brief Esse enum serve para guarda a escolha do úsuario referente a ordem de impressão(crescente ou decrescente)
 */
enum ordenacaot{
    crescente,
    decrescente,
};
/**
 * @brief Esse enum serve para guarda a escolha do úsuario referente ao que vai ser levado em consideração na ordem de impressão.
 */
enum ordenacaop{
    f,
    t,
    c,
    d,
    b,
    s,
    a,
};
/**
 * @brief essa função é responsável por determinar os possíveis estados durante a iteração de cada linha do arquivo.
 */
enum estados{
    neutro,
    estritamentecodigo1,
    estritamentecodigo2,
    estritamentecoment,
    estritamentedcoment

};
/**
 * @brief struct para determinar o tipo de um arquivo o qual conterá informações como tipo,nome,linha de código e etc.
 */
struct fileinfos{
    int lcodigo;
    int lcoment;
    int ldcoment;
    int lbranco;
    int ltotais;
    char nome[300];
    std::string tipo;
    std::string nomer;
};
void imprimirajuda(){
    std::cout<<"Bem-vindo ao sloc cpp, versão 1.0, (c) DIMAp/UFRN.";
    std::cout<<"NOME\n";
    std::cout<<" sloc - contador de linhas de código.\n";
    std::cout<<"SÍNTESE\n";
    std::cout<<" sloc [-h | --help] [-r] [(-s | -S) f|t|c|d|b|s|a] <arquivo | diretório>\n";
    std::cout<<"EXEMPLOS\n";
    std::cout<<" sloc main.cpp sloc.cpp\n";
    std::cout<<"  AVISO:coloque o caminho completo dos arquivos ou diretórios\n";
    std::cout<<"   Conta as loc, comentários e linhas em branco dos arquivos fonte 'main.cpp' e 'sloc.cpp'\n";
    std::cout<<" sloc -r -s c source\n";
    std::cout<<"   Conta loc, comentários e linhas em branco de todos os arquivos fonte C/C++ recursivamente dentro de 'source'\n";
    std::cout<<"DESCRIÇÃO\n";
    std::cout<<"  O sloc conta o número de **linhas de código (LOC)**, comentários e linhas em branco encontradas em uma lista de\n";
    std::cout<<" arquivos ou diretórios passados como último argumento (após as opções).\n";
    std::cout<<" Após o processo de contagem, o programa imprime na saída padrão uma tabela resumindo as informações coletadas,\n";
    std::cout<<" por cada arquivo fonte e/ou diretório fornecido.\n";
    std::cout<<" É possível informar quais campos o sloc deve usar para ordenar os dados, bem como se os dados devem ser\n";
    std::cout<<" apresentados em ordem numérica crescente ou decrescente.\n";
    std::cout<<"OPÇÕES:\n";
    std::cout<<" -h\n";
    std::cout<<"   Exibe esta informação.\n";
    std::cout<<" -r\n";
    std::cout<<"    Procura arquivos recursivamente no diretório fornecido.\n";
    std::cout<<" -s f|t|c|d|b|s|a\n";
    std::cout<<"   Ordena a tabela em ordem CRESCENTE por (f)nome, (t)ipo de arquivo, (c)omentários,\n";
    std::cout<<"   (d)ocumentação, (b)lank lines, (s)loc, ou (a)mbos. O padrão é mostrar arquivos na ordem de aparição.\n";
    std::cout<<" -S f|t|c|d|b|s|a\n";
    std::cout<<"   Ordena a tabela em ordem DECRESCENTE por (f)nome, (t)ipo de arquivo, (c)omentários,";
    std::cout<<"   (d)ocumentação, (b)lank lines, (s)loc, ou (a)mbos. O padrão é mostrar arquivos na ordem de aparição.\n";
    std::cout<<"AVISO:coloque o caminho completo dos arquivos ou diretórios\n";
}
/**
 * @brief serve para determinar o arquivo com maior nome.
 * o funcionamento dela é similar a uma função padrão de achar o maior membro de um vetor
 */
int maiornome(std::vector<fileinfos> arquivos){
    int maior=0;
    for(int i=0;i<arquivos.size();i++){
        if(arquivos[i].nomer.size()>maior){
            maior=arquivos[i].nomer.size();
        }
    }
    return maior;
}
/**
 * @brief vai ordenar o arquivo seguindo as demandas do usuário
 * a ordenação é no modelo selection sort
 */
void ordenar(std::vector<fileinfos>& arquivos,ordenacaot tordem,ordenacaop pordem){
    for(int i=0;i<arquivos.size();i++){//loop para percorrer cada membro do vetor
        int min=i;//variaveis que representam o menor e maior valor de certo segmento vetor
        int max=i;
        for(int j=i;j<arquivos.size();j++){
            switch(pordem){//confere a ordem solicitada 
                case f:
                if(arquivos[j].nomer.size() < arquivos[min].nomer.size()){//busca o menor ou maior elemento a partir de certo ponto
                    min=j;
                }
                if(arquivos[j].nomer.size() > arquivos[max].nomer.size()){
                    max=j;
                }
                break;
                case t:
                if(arquivos[j].tipo.size() < arquivos[min].tipo.size()){
                    min=j;
                }
                if(arquivos[j].tipo.size() > arquivos[min].tipo.size()){
                    max=j;
                }
                break;
                case c:
                if(arquivos[j].lcoment<arquivos[min].lcoment){
                    min=j;
                }
                if(arquivos[j].lcoment>arquivos[max].lcoment){
                    max=j;
                }
                break;
                case d:
                if(arquivos[j].ldcoment<arquivos[min].ldcoment){
                    min=j;
                }
                if(arquivos[j].ldcoment>arquivos[max].ldcoment){
                    max=j;
                }
                break;
                case b:
                if(arquivos[j].lbranco<arquivos[min].lbranco){
                    min=j;
                }
                if(arquivos[j].lbranco>arquivos[max].lbranco){
                    max=j;
                }
                break;
                case s:
                if(arquivos[j].lcodigo<arquivos[min].lcodigo){
                    min=j;
                }
                if(arquivos[j].lcodigo>arquivos[min].lcodigo){
                    max=j;
                }
                break;
                case a:
                if(arquivos[j].ltotais<arquivos[min].ltotais){
                    min=j;
                }
                if(arquivos[j].ltotais>arquivos[max].ltotais){
                    max=j;
                }
                break;
                default:
                break;
            }
            }
            if(tordem==crescente){//verifica se os arquivos serão exibidos por ordem crescente ou drescente
            std::swap(arquivos[i],arquivos[min]);//troca os valores
            }
            else{
            std::swap(arquivos[i],arquivos[max]);
            }
        
    }

}/**
 * @brief Função para auxiliar na impressão tabela
 * vê o número de digitos da porcentagem do número de linhas /codigos/doccoment/coment/branco
 */
int tamanhosig(std::string str){
    if(str.size()==1){//caso seja algo 5.0% ou 2.5%
        return 2;
    }
    else if(str.size()==2||str=="100"){//caso seja 
        return 3;
    }
}/**
 * @brief Função para auxiliar na impressão tabela
 */
std::string arredondarmais(std::string str){
    int i=0;
    std::string stround;
    while(str[i]!='.'){
        stround.push_back(str[i]);
        i++;
    }
    return stround;
}
/**
 * @brief determina o tipo do arquivo
 */
std::string determinartipo(std::string arquivo){
    std::string tipo;
    int i=arquivo.size();
    std::string cpp="cpp";
    std::string hpp="hpp";
    std::string c="c";
    std::string h="h";
    while(arquivo[i]!='.'){
        tipo.push_back(arquivo[i]);
        i--;
    }//percorre o nome do arquivo até achar um "/", o que vem após é a sua extensão
    std::reverse(tipo.begin(),tipo.end());
    const char* temptipo=tipo.c_str();
    if(strcmp(temptipo,"cpp") == 0){//classica o tipo do arquivo de acordo com sua extensão
        tipo="C++";
    }
    else if(strcmp(temptipo,"c") == 0){
        tipo="C";
    }
    else if(strcmp(temptipo,"hpp") == 0 ||strcmp(temptipo,"h") == 0 ){
        tipo="C/C++ header";
    }
    else{
        tipo="invalido";
    }
    return tipo;
}
/**
 * @brief retorna o nome do arquivo sem o caminho completo
 */
std::string determinarnome(std::string nomefluxo){
    std::string nome;
    int i=nomefluxo.size();
    while(nomefluxo[i]!='\\' && nomefluxo[i]!= '/'){//o nome será tudo até a primeira "/"
        nome.push_back(nomefluxo[i]);
        i--;
    }
    std::reverse(nome.begin(),nome.end());
    return nome;
}
/** 
*@brief remove os espaços laterais de uma linha do arquivo para facilitar na análise
*/
std::string removerEspacosExtremos(const std::string& str) {
    size_t primeiro = str.find_first_not_of(" \t\n\r\f\v");
    if (primeiro == std::string::npos) {
        return "";
    }
    size_t ultimo = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(primeiro, ultimo - primeiro + 1);
}/** 
*@brief processa as entradas dadas pelo usuário
*/
int Running_options(int& agrc, char* agrv[],ordenacaop& pordem, ordenacaot& tordem,bool& recursaoativa,std::vector<int>& arquivospp,bool& ordemativa){
    char temp;
    int narquivos;
    for(int i=1;i<agrc;i++){
        if(strcmp(agrv[i],"-S")==0 || strcmp(agrv[i],"-s")==0 ){// Caso haja um "-s" ou "-S" significa que o usuário determinou uma ordem
        ordemativa=true;
        if(strcmp(agrv[i],"-S")==0){
            tordem=decrescente;
        }
        else{
            tordem=crescente;
        }
            temp=agrv[i+1][0];//o que vem a seguir é o que será levado em conta na ordenação
            switch(temp){
                case 'f':
                pordem=f;
                break;
                case 't':
                pordem=t;
                break;
                case 'c':
                pordem=c;
                break;
                case 'd':
                pordem=d;
                break;
                case 'b':
                pordem=b;
                break;
                case 's':
                pordem=s;
                break;
                case 'a':
                pordem=a;
                break;
                default:
                std::cout<<"Solicite uma forma válida de ordenar";// caso o usuário solicite um modo de ordenação inválido
                return 1;
                break;
            }
            i++;
        }
        if(strcmp(agrv[i],"-r")==0){// o usuário solicitou a análise recursiva dos diretórios
            recursaoativa=true;
        }
        if(strcmp(agrv[i],"-h")==0){
            imprimirajuda();
        }
        else{//tudo fora isso será considerado um arquivo a ser analisado
            arquivospp.push_back(i);
        }
    }
}
/**
 * 
 *@brief recebe um arquivo e determina a quantidade de linhas de códigos/comentário/doc comentários em branco/
*/
void lerarquivo(std::string nomef,std::vector<fileinfos> &arquivos){
            bool codigo;//uma série de variáreis que vão ajudar na análise do arquivo
            bool comentario;
            bool dcomentario;
            bool branco;
            fileinfos arquivo;//uma série de variáreis que vão armazenar os dados do arquivo
            arquivo.lcodigo=0;
            arquivo.lcoment=0;
            arquivo.ldcoment=0;
            arquivo.lbranco=0;
            arquivo.ltotais=0;
            arquivo.nomer=determinarnome(nomef);//Determina o nome do arquivo sem seu caminho
            const char* nometemp=nomef.c_str();
            strcpy(arquivo.nome,nometemp);
            arquivo.tipo=determinartipo(arquivo.nome);//Determina o tipo do arquivo
            if(arquivo.tipo!="invalido"){//caso o tipo do arquivo não seja suportado a análise é encerrada e ele não será exibido na tabela
            std::ifstream arquivol(nomef);
            if (!arquivol.is_open()) {
            std::cerr << "Não foi possivel abrir "<<arquivo.nomer<<" para leitura" << std::endl;
            }
            std::string linha;
            estados estado=neutro;
            while (std::getline(arquivol, linha)) {//iterando sobre cada linha do arquivo
                arquivo.ltotais++;
                std::string clinha = removerEspacosExtremos(linha);
                dcomentario=false;
                codigo=false;
                comentario=false;
                branco=true;
                bool flag=false;
                for(int i=0;i<clinha.size();i++){//tamanho de caracteres na linha
                    switch(estado){
                        case neutro:
                        branco=false;//se chegou aqui é porque não é uma linha em branco
                        if(clinha[i]=='\''){//se foi achado uma ' a partir de agora tudo é código até ser achado outra '
                            codigo=true;
                            estado=estritamentecodigo1;//troca o estado
                        }
                        else if(clinha[i]=='\"'){//se foi achado uma " a partir de agora tudo é código até ser achado outra "
                            codigo=true;
                            estado=estritamentecodigo2;//troca o estado
                        }
                        else if(clinha[i]=='/'&&clinha[i+1]=='*'){// se foi achado um /* verifica se é de um bloco de doccomentário ou de comentário
                            if((clinha[i+2]=='*'||clinha[i+2]=='!')&&clinha[i+3]!='/'){
                                dcomentario=true;
                                estado=estritamentedcoment;//troca o estado se tiver mais um * ou !
                                i++;
                                i++; 
                            }
                            else{
                                comentario=true;
                                estado=estritamentecoment;//se não tiver um * troca para o estado comentário
                                i++;
                            }
                        }
                        else if(clinha[i]=='/'&&clinha[i+1]=='/'){// após achar uma // verifica se não tem uma / em seguida para garantir que não é uma linha de comentário
                            if(clinha[i+2]=='/'){// uma sequência de /// indica que o resto da linha é de doccomentário após isso passa para próxima iteração
                                dcomentario=true;
                                i=clinha.size();
                            }
                            else{
                                comentario=true;
                                i=clinha.size();
                            }
                        }
                        else {
                            codigo=true;//caso nenhuma das condições tenha sido cumprida significa que esse caractere faz parte de um código
                        }
                        break;

                        case estritamentecodigo1://considera tudo código até ser achado um '
                        branco=false;
                        codigo=true;
                        if(clinha[i]=='\\'&& flag==false){//tratamento de caso especial: a \ anula o ', logo se o próximo caracter após a \ for um ' o estado precisa se manter 
                            flag=true;
                            continue;
                        }
                        if(clinha[i]=='\''&& !flag){
                            estado=neutro;
                        }
                        flag=false;
                        break;

                        case estritamentecodigo2://mesma ideia  do outro só que para "
                        branco=false;
                        codigo=true;
                        if(clinha[i]=='\\'&& flag==false){
                            flag=true;
                            continue;
                        }
                        if(clinha[i]=='\"'&& !flag){
                            estado=neutro;
                            
                        }
                        flag=false;
                        break;

                        case estritamentecoment:// tudo é considerado comentário até ser achado um */
                        comentario=true;
                        if(clinha[i]=='*'&&clinha[i+1]=='/'){
                            estado=neutro;
                            i++;
                            branco=false;
                        }
                        break;

                        case estritamentedcoment:// tudo é considerado doc comentário até ser achado um */
                        dcomentario=true;
                        if(clinha[i]=='*'&&clinha[i+1]=='/'){
                            estado=neutro;
                            i++;
                            branco=false;
                        }
                        break;
                    }
                }
                //classifica a linha, adicionando essa informação aos dados arquivo
                if(codigo){
                    arquivo.lcodigo++;
                }
                if(comentario || estado==estritamentecoment){
                    arquivo.lcoment++;
                }
                if(dcomentario || estado==estritamentedcoment){
                    arquivo.ldcoment++;
                }
                if(branco && estado!=estritamentecoment && estado!=estritamentedcoment){
                    arquivo.lbranco++;
                }
            }
            arquivol.close();
            arquivos.push_back(arquivo);//adiciona esse os dados do arquivo nesse vector para serem exibidos posteriormente na tabela
    }
}/** 
*@brief processa as entradas dadas pelo usuário
*/
void lerfluxo(const char* dir,std::vector<fileinfos> &arquivos,bool recursaoativa){
    bool codigo;
    bool comentario;
    bool dcomentario;
    bool branco;
    //std::cout<<dir<<"\n";
    DIR *di=opendir(dir);//tenta abrir um fluxo como um diretório
    if(di){//caso tenha sido possível abrir isso significa que esse fluxo é um diretório
    struct dirent* entrada;
    while(entrada =readdir(di)){//itera sobre o diretório
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0){
            continue;
        }
        if (entrada->d_type == DT_DIR && recursaoativa){//caso tenha um diretório dentro do diretório atual e o usuário tenha solicitado a busca recursiva
            std::string sdir(dir);
            std::string ndir(entrada->d_name);
            std::string tempc= sdir+"\\"+ndir;//montando caminho para o diretório encontrado
            char* tempcc = const_cast<char*>(tempc.c_str());
            lerfluxo(tempcc,arquivos,recursaoativa);//chamada recursiva da função sobre o diretório encontrado
        }
        if(entrada->d_type == DT_REG){//se for achado um arquivo regular no diretório será aplicado nele a função "lerarquivo" nele
            std::string sdir(dir);
            std::string narq(entrada->d_name);
            std::string tempf=sdir+"\\"+narq;
            lerarquivo(tempf,arquivos);
        }
    }
    closedir(di);
}
else{//se o fluxo não é um diretório então ele pode ser um arquivo
    lerarquivo(dir,arquivos);
}
}
int main(int agrc,char* agrv[]) {
    if(agrc==1){//caso o usuário apenas execute o programa sem colocar nada
        imprimirajuda();
    }
    std::vector<int> arquivospp;
    ordenacaot tordem=crescente;
    ordenacaop pordem=s;
    bool recursaoativa=false;
    std::vector<fileinfos> arquivos;
    bool ordemativa;
    int resultado;
    resultado=Running_options(agrc,agrv,pordem,tordem,recursaoativa,arquivospp,ordemativa);//verifica as entradas
    if(resultado==1){//fecha o programa caso o usuário tenha solicitado uma forma inválida de ordenação
        return 1;
    }
    for(int i=0;i<arquivospp.size();i++){//lê os arquivos dado pelo usuário
        lerfluxo(agrv[arquivospp[i]],arquivos,recursaoativa);
    }
    if(arquivos.size()==0){//caso não tenha nenhum arquivo no fluxo dado pelo usuário
        std::cout<<"Nenhum arquivo válido";
        return 1;
    }
    if(ordemativa){//caso o usuário tenha solicitado alguma ordem
    ordenar(arquivos,tordem,pordem);
    }
    //impressão da tabela
    std::cout<<"Arquivos processados: "<<arquivos.size()<<"\n";
    std::cout<<"Nome do arquivo             ";
    for(int i=0;i<maiornome(arquivos)-16;i++){
            std::cout<<" ";
    }
    std::cout<<"Linguagem      ";
    if(16<maiornome(arquivos)){
        for(int i=0;i<16-maiornome(arquivos);i++){
            std::cout<<" ";
        }
    }
    std::cout<<"Comentarios        ";
    std::cout<<"Doc Comentarios    ";
    std::cout<<"Em branco         ";
    std::cout<<"Codigo   ";
    std::cout<<"# de linhas\n";
    int sumlcodigo=0;
    int sumlcoment=0;
    int sumldcoment=0;
    int sumlbranco=0;
    int sumltotais=0;
    float porlcodigo;
    float porlcoment;
    float porldcoment;
    float porlbranco;

    for(const auto a:arquivos){
        porlcodigo=(static_cast<float>(a.lcodigo)/a.ltotais)*100;
        porlcoment=(static_cast<float>(a.lcoment)/a.ltotais)*100;
        porldcoment=(static_cast<float>(a.ldcoment)/a.ltotais)*100;
        porlbranco=(static_cast<float>(a.lbranco)/a.ltotais)*100;
        std::cout<<a.nomer;
        if(16>maiornome(arquivos)){
        for(int i=0;i<16-a.nomer.size();i++){
            std::cout<<" ";
        }
        }
        else{
            for(int i=0;i<maiornome(arquivos)-a.nomer.size();i++){
                std::cout<<" ";
            }

        }
        std::cout<<"             ";
        std::cout<<a.tipo;
        for(int i=0;i<12-a.tipo.size();i++){
            std::cout<<" ";
        }
        std::cout<<"   ";
        std::cout << std::fixed << std::setprecision(1);
        std::cout<<a.lcoment<<"("<<porlcoment<<"%)";
        std::string strc = std::to_string(a.lcoment);
        std::string strcp = arredondarmais(std::to_string(std::round(porlcoment)));
        for(int i=0;i<6-(strc.size()+tamanhosig(strcp));i++){
            std::cout<<" ";
        }
        std::cout<<"         ";
        std::cout << std::fixed << std::setprecision(1);
        std::cout<<a.ldcoment<<"("<<porldcoment<<"%)";
        std::string strc1 = std::to_string(a.ldcoment);
        std::string strcp1 = arredondarmais(std::to_string(std::round(porldcoment)));
        for(int i=0;i<6-(strc1.size()+tamanhosig(strcp1));i++){
            std::cout<<" ";
        }
        std::cout<<"         ";
        std::cout << std::fixed << std::setprecision(1);
        std::cout<<a.lbranco<<"("<<porlbranco<<"%)";
        std::string strc2 = std::to_string(a.lbranco);
        std::string strcp2 = arredondarmais(std::to_string(std::round(porlbranco)));
        for(int i=0;i<6-(strc2.size()+tamanhosig(strcp2));i++){
            std::cout<<" ";
        }
        std::cout<<"        ";
        std::cout << std::fixed << std::setprecision(1);
        std::cout<<a.lcodigo<<"("<<porlcodigo<<"%)";
        std::string strc3 = std::to_string(a.lcodigo);
        std::string strcp3 = arredondarmais(std::to_string(std::round(porlcodigo)));
        for(int i=0;i<6-(strc3.size()+tamanhosig(strcp3));i++){
            std::cout<<" ";
        }
        std::cout<<"       ";
        std::cout<<a.ltotais<<" ";
        std::cout<<"\n";
        sumlcodigo+=a.lcodigo;
        sumlcoment+=a.lcoment;
        sumlbranco+=a.lbranco;
        sumldcoment+=a.ldcoment;
        sumltotais+=a.ltotais;
    }
    std::cout<<"SUM                                        ";
    for(int i=0;i<maiornome(arquivos)-16;i++){
        std::cout<<" ";
    }
    std::cout<<sumlcoment<<"                  ";
    std::cout<<sumldcoment<<"                  ";
    std::cout<<sumlbranco<<"                 ";
    std::cout<<sumlcodigo<<"              ";
    std::cout<<sumltotais<<"\n";
    return 0;
}
