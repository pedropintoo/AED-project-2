%% Constantes a alterar.....

caseNames = ["Sucesso (Pior caso)", "Sucesso (Melhor caso)","Insucesso (Pior caso)", "Insucesso (Melhor caso)"];
caseFileNames = ["Success_worstCase_", "Success_bestCase_","Insuccess_worstCase_", "Insuccess_bestCase_"];
casePathNames = ["SuccessWorst", "SuccessBest","InsuccessWorst", "InsuccessBest"];

CASE = 0;
% 0-> Sucesso - Pior caso
% 1-> Sucesso - Melhor caso
% 2-> Insucesso - Pior caso
% 3-> Insucesso - Melhor caso

ONLY = 0;
% 1-> Algoritmo 1
% 2-> Algoritmo 2
% 3-> Algoritmo 3
% ...-> Mostra todos

% Vertex -> numero de vertices
vertex_min = 2;
vertex_inc = 1;
vertex_max = 250;

printAll = 1;

colorV1 = "o-"; 
colorV2 = "ob-"; 
colorV2alternative = "ob-"; % Por causa da sobreposicao no grafico das iteracoes!
colorV3 = "o-"; % Yellow: "[0.9290 0.6940 0.1250]"

customLegend = caseNames(CASE+1);

% Controlo dos algoritmos que iram ser apresentados
show1 = 0;
show2 = 0;
show3 = 0;
switch (ONLY)
    case 1 % Algoritmo 1
        fileName = "onlyAlg1_";
        pathName = "only";
        show1 = 1;
    case 2 % Algoritmo 2
        fileName = "onlyAlg2_";
        pathName = "only";
        show2 = 1;
    case 3 % Algoritmo 3
        fileName = "onlyAlg3_";
        pathName = "only";
        show3 = 1;
    otherwise % Desativado
        show1 = 1;
        show2 = 1;
        show3 = 1;
        fileName = caseFileNames(CASE+1);
        pathName = casePathNames(CASE+1);
end

%% Executar e ler o output

% Executar
status = system(sprintf("./execute_topoTest.sh %d %d %d %d",CASE,vertex_min,vertex_inc,vertex_max)); 

% Ler dados
file = fopen("data_topoTests.txt","r");
formatSpec = '%d %f %f %d';
data = textscan(file, formatSpec);
fclose(file);

verticesArray = double(data{1}); % Vertices
timeArray = double(data{2}); % 1
caltimeArray = double(data{3}); % Not used!
ITERATIONSArray = double(data{4}); % 2

%% Tempo de execucao em funcao de n
f1_time = figure(1);

if (show1)
    hold on;
    %Version 1
    plot(verticesArray(1:3:end),timeArray(1:3:end),colorV1,'DisplayName',sprintf("Algoritmo 1 - %s",customLegend));
end

if (show2)
    hold on;
    % Version 2
    plot(verticesArray(2:3:end),timeArray(2:3:end),colorV2,'DisplayName',sprintf("Algoritmo 2 - %s",customLegend));  
end

if (show3)
    hold on;
    % Version 3
    plot(verticesArray(3:3:end),timeArray(3:3:end),colorV3,'color',[0.9290 0.6940 0.1250],'DisplayName',sprintf("Algoritmo 3 - %s",customLegend));
end

grid on
title("Tempo de execucao em funcao de n Vertices")
xlabel("Numero de vertices do Digrafo")
ylabel("Tempo de execucao (segundos)")
legend

if printAll
  f1_time.PaperType='A4';
  f1_time.PaperOrientation='landscape';
  f1_time.PaperUnits='points';
  print(sprintf("%s/time/%stime_V%d.pdf",pathName,fileName,vertex_max),'-dpdf','-noui','-fillpage');
end


%% Numero de iteracoes em funcao de n
f2_iterations = figure(2);

if (show1)
    hold on;
    %Version 1
    plot(verticesArray(1:3:end),ITERATIONSArray(1:3:end),colorV1,'DisplayName',sprintf("Algoritmo 1 - %s",customLegend));
end

if (show2)
    hold on;
    % Version 2
    plot(verticesArray(2:3:end),ITERATIONSArray(2:3:end),colorV2alternative,'DisplayName',sprintf("Algoritmo 2 - %s",customLegend));
end

if (show3)
    hold on;
    % Version 3
    plot(verticesArray(3:3:end),ITERATIONSArray(3:3:end),colorV3,'color',[0.9290 0.6940 0.1250],'DisplayName',sprintf("Algoritmo 3 - %s",customLegend));
end

grid on
title("Numero de Iteracoes em funcao de n Vertices")
xlabel("Numero de vertices do Digrafo")
ylabel("Numero de iteracoes (ITERATIONS)")
legend

if printAll
  f2_iterations.PaperType='A4';
  f2_iterations.PaperOrientation='landscape';
  f2_iterations.PaperUnits='points';
  print(sprintf("%s/iterations/%siterations_V%d.pdf",pathName,fileName,vertex_max),'-dpdf','-noui','-fillpage');
end
