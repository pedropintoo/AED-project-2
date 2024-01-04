%% Constantes a alterar.....

OPTION = 0; 
% 0-> Por size (mesma janela de blur, imagem varia)
% 1-> Por window (mesma imagem, janela de blur varia)

% Size -> largura da imagem (sendo a imagem quadrada) 
size_min = 1;
size_inc = 1;
size_max = 50; % w = h

% Window -> janela do blur (sendo a janela quadrada) 
window_min = 1;
window_inc = 1;
window_max = 70; % dx = dy

onlyV2 = 1; % 1-> Graficos com apenas a versao 2 (algoritmo melhorado)
% Podemos sobrepor no mesmo grafico utilizando os conceitos de cima

printAll = 1;

colorV1 = "o-";
colorV2 = "o-";
% Na OPTION == 0:
% Para sobrepor ao grafico outro com window_max=2 (dx=dy), basta retirar "r" e "b" das
% cores de cima e mudar os valores window_max e executar "Executar e ler dados"


onlyV2path = "";

if (onlyV2 == 1)
    onlyV2path = "onlyV2_";
end


% Executar e ler dados
% generate the file text with data
if (OPTION == 0) 
    status = system(sprintf("./execute_blurTests.sh %d %d %d %d %d %d",0,size_min,size_inc,size_max,window_max,window_max)); 
    customLegend = sprintf("W%dx%d",window_max,window_max);
    path = "bySize";
    customLabelx = "Numero de pixeis da imagem";
    customTitle = "n";
else
    status = system(sprintf("./execute_blurTests.sh %d %d %d %d %d %d",1,window_min,window_inc,window_max,size_max,size_max)); 
    customLegend = sprintf("S%dx%d",size_max,size_max);
    path = "byWindow";
    customLabelx = "Valor 'dx' da janela de blur (dx=dy)";
    customTitle = "dx";
end


file = fopen("data_blurTests.txt","r");
formatSpec = '%d %f %f %d %d %d %d';
data = textscan(file, formatSpec);
fclose(file);

nPixelsArray = double(data{1});
timeArray = double(data{2}); % 1
caltimeArray = double(data{3});
PIXMEMArray = double(data{4}); % 2
COMPARISONSArray = double(data{5}); % 3
OPERATIONSArray = double(data{6}); % 4

%% Tempo de execucao em funcao de n
f1_time = figure(1);

if (onlyV2 == 0)
    %Version 1
    plot(nPixelsArray(1:2:end),timeArray(1:2:end),colorV1,'DisplayName',sprintf("Versao 1 - %s",customLegend));
end
hold on;
% Version 2
plot(nPixelsArray(2:2:end),timeArray(2:2:end),colorV2,'DisplayName',sprintf("Versao 2 - %s",customLegend));

grid on
title(sprintf("Tempo de execucao em funcao de %s",customTitle))
xlabel(customLabelx)
ylabel("Tempo de execucao (segundos)")
legend

if printAll
  f1_time.PaperType='A4';
  f1_time.PaperOrientation='landscape';
  f1_time.PaperUnits='points';
  print(sprintf("%s/time/%stime_S%dx%d_W%dx%d.pdf",path,onlyV2path,size_max,size_max,window_max,window_max),'-dpdf','-noui','-fillpage');
end


%% Numero de acessos (PIXMEM) em funcao de n
f2_pixmem = figure(2);

if (onlyV2 == 0)
    %Version 1
    plot(nPixelsArray(1:2:end),PIXMEMArray(1:2:end),colorV1,'DisplayName',sprintf("Versao 1 - %s",customLegend));
end
hold on;
% Version 2
plot(nPixelsArray(2:2:end),PIXMEMArray(2:2:end),colorV2,'DisplayName',sprintf("Versao 2 - %s",customLegend));

grid on
title(sprintf("Numero de acessos (PIXMEM) em funcao de %s",customTitle))
xlabel(customLabelx)
ylabel("Numero de acessos (PIXMEM)")
legend

if printAll
  f2_pixmem.PaperType='A4';
  f2_pixmem.PaperOrientation='landscape';
  f2_pixmem.PaperUnits='points';
  print(sprintf("%s/pixmem/%spixmem_S%dx%d_W%dx%d.pdf",path,onlyV2path,size_max,size_max,window_max,window_max),'-dpdf','-noui','-fillpage');
end

%% Numero de comparacoes em funcao de n
f3_comparisons = figure(3);

if (onlyV2 == 0)
    %Version 1
    plot(nPixelsArray(1:2:end),COMPARISONSArray(1:2:end),colorV1,'DisplayName',sprintf("Versao 1 - %s",customLegend));
end
hold on;
% Version 2
plot(nPixelsArray(2:2:end),COMPARISONSArray(2:2:end),colorV2,'DisplayName',sprintf("Versao 2 - %s",customLegend));

grid on
title(sprintf("Numero de comparacoes em funcao de %s",customTitle))
xlabel(customLabelx)
ylabel("Numero de comparacoes (COMPARISONS)")
legend

if printAll
  f3_comparisons.PaperType='A4';
  f3_comparisons.PaperOrientation='landscape';
  f3_comparisons.PaperUnits='points';
  print(sprintf("%s/comparisons/%scomparisons_S%dx%d_W%dx%d.pdf",path,onlyV2path,size_max,size_max,window_max,window_max),'-dpdf','-noui','-fillpage');
end

%% Numero de operacoes relevantes (OPERATIONS) em funcao de n
f4_operations = figure(4);

if (onlyV2 == 0)
    %Version 1
    plot(nPixelsArray(1:2:end),OPERATIONSArray(1:2:end),colorV1,'DisplayName',sprintf("Versao 1 - %s",customLegend));
end
hold on;
% Version 2
plot(nPixelsArray(2:2:end),OPERATIONSArray(2:2:end),colorV2,'DisplayName',sprintf("Versao 2 - %s",customLegend));

grid on
title(sprintf("Numero de operacoes (relevantes) em funcao de %s",customTitle))
xlabel(customLabelx)
ylabel("Numero de operacoes (OPERATIONS)")
legend

if printAll
  f4_operations.PaperType='A4';
  f4_operations.PaperOrientation='landscape';
  f4_operations.PaperUnits='points';
  print(sprintf("%s/operations/%soperations_S%dx%d_W%dx%d.pdf",path,onlyV2path,size_max,size_max,window_max,window_max),'-dpdf','-noui','-fillpage');
end