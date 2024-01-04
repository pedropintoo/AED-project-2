%% Constantes a alterar.....

CASE = 0;
% 0-> Sucesso - Melhor/Pior caso
% 1-> Nao Sucesso - Pior caso
% 2-> Nao Sucesso - Melhor caso

OPTION = 1; 
% 0-> Por Edge (mesmo numero de vertices)
% 1-> Por Vertex (mesmo numero de arestas)

% Edge -> numero de arestas 
edge_min = 1;
edge_inc = 1;
edge_max = 5;

% Vertex -> numero de vertices
vertex_min = 100;
vertex_inc = 10;
vertex_max = 200;

% ????????????????????????????????????
onlyV2 = 0; % 1-> Graficos com apenas a versao 2 (algoritmo melhorado)
% Podemos sobrepor no mesmo grafico utilizando os conceitos de cima

printAll = 1;

colorV1 = "or-"; % Red: "#A2142F"
colorV2 = "ob--"; % Blue: "#0072BD"
colorV3 = "o-"; % Green: "#77AC30"
% Na OPTION == 0:
% Para sobrepor ao grafico outro com window_max=2 (dx=dy), basta retirar "r" e "b" das
% cores de cima e mudar os valores window_max e executar "Executar e ler dados"

preName = "";
onlyV2path = "";

if (onlyV2 == 1)
    onlyV2path = "onlyV2_";
end


% Executar e ler dados
% generate the file text with data
if (CASE == 0)
    if (OPTION == 0) 
        status = system(sprintf("./execute_topoSuccess.sh %d %d %d %d %d %d",0,edge_min,edge_inc,edge_max,vertex_max)); 
        customLegend = sprintf("V%d",vertex_max);
        preName = "success_byEdge_";
        path = "Success/byEdge";
        customLabelx = "Numero de arestas do Grafo";
        customTitle = "Variaçao do numero de arestas";
    else
        status = system(sprintf("./execute_topoSuccess.sh %d %d %d %d %d",1,vertex_min,vertex_inc,vertex_max,edge_max)); 
        customLegend = sprintf("E%d",edge_max);
        preName = "success_byVertex_";
        path = "Success/byVertex";
        customLabelx = "Numero de vertices do Grafo";
        customTitle = "Variaçao do numero de vertices";
    end
end    


file = fopen("data_topoTests.txt","r");
formatSpec = '%d %f %f %d %d';
data = textscan(file, formatSpec);
fclose(file);

nStudyArray = double(data{1}); % Vertices or Edges
timeArray = double(data{2}); % 1
caltimeArray = double(data{3});
ITERATIONSArray = double(data{4}); % 2
OPERATIONSArray = double(data{5}); % 3

%% Tempo de execucao em funcao de n
f1_time = figure(1);


%Version 1
plot(nStudyArray(1:3:end),timeArray(1:3:end),colorV1,'DisplayName',sprintf("Versao 1 - %s",customLegend));

hold on;
% Version 2
plot(nStudyArray(2:3:end),timeArray(2:3:end),colorV2,'DisplayName',sprintf("Versao 2 - %s",customLegend));

hold on;
% Version 2
plot(nStudyArray(3:3:end),timeArray(3:3:end),colorV3,'DisplayName',sprintf("Versao 3 - %s",customLegend));

grid on
title(sprintf("Tempo de execucao em funcao de %s",customTitle))
xlabel(customLabelx)
ylabel("Tempo de execucao (segundos)")
legend

if printAll
  f1_time.PaperType='A4';
  f1_time.PaperOrientation='landscape';
  f1_time.PaperUnits='points';
  print(sprintf("%s/time/%s%stime_E%d_V%d.pdf",path,preName,onlyV2path,edge_max,vertex_max),'-dpdf','-noui','-fillpage');
end


%% Numero de iteracoes em funcao de n
f2_iterations = figure(2);

%Version 1
plot(nStudyArray(1:3:end),ITERATIONSArray(1:3:end),colorV1,'DisplayName',sprintf("Versao 1 - %s",customLegend));

hold on;
% Version 2
plot(nStudyArray(2:3:end),ITERATIONSArray(2:3:end),colorV2,'DisplayName',sprintf("Versao 2 - %s",customLegend));

hold on;
% Version 2
plot(nStudyArray(3:3:end),ITERATIONSArray(3:3:end),colorV3,'DisplayName',sprintf("Versao 3 - %s",customLegend));

grid on
title(sprintf("Iteracoes em funcao de %s",customTitle))
xlabel(customLabelx)
ylabel("Numero de iteracoes (ITERATIONS)")
legend

if printAll
  f2_iterations.PaperType='A4';
  f2_iterations.PaperOrientation='landscape';
  f2_iterations.PaperUnits='points';
  print(sprintf("%s/iterations/%s%siterations_E%d_V%d.pdf",path,preName,onlyV2path,edge_max,vertex_max),'-dpdf','-noui','-fillpage');
end

%% Numero de operacoes relevantes (OPERATIONS) em funcao de n
f3_operations = figure(3);

%Version 1
plot(nStudyArray(1:3:end),OPERATIONSArray(1:3:end),colorV1,'DisplayName',sprintf("Versao 1 - %s",customLegend));

hold on;
% Version 2
plot(nStudyArray(2:3:end),OPERATIONSArray(2:3:end),colorV2,'DisplayName',sprintf("Versao 2 - %s",customLegend));

hold on;
% Version 2
plot(nStudyArray(3:3:end),OPERATIONSArray(3:3:end),colorV3,'DisplayName',sprintf("Versao 3 - %s",customLegend));

grid on
title(sprintf("Operacoes em funcao de %s",customTitle))
xlabel(customLabelx)
ylabel("Numero de operacoes (OPERATIONS)")
legend

if printAll
  f3_operations.PaperType='A4';
  f3_operations.PaperOrientation='landscape';
  f3_operations.PaperUnits='points';
  print(sprintf("%s/operations/%s%soperations_E%d_V%d.pdf",path,preName,onlyV2path,edge_max,vertex_max),'-dpdf','-noui','-fillpage');
end
