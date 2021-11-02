close all;
clear;
load data_set_full_1.mat;
x = linspace(1,6,6);

%% Calculate Means
mean_atelier_low = [mean(atelier_low(:,1)) mean(atelier_low(:,2)) mean(atelier_low(:,3)) mean(atelier_low(:,4)) mean(atelier_low(:,5)) mean(atelier_low(:,6))];
mean_atelier_med = [mean(atelier_med(:,1)) mean(atelier_med(:,2)) mean(atelier_med(:,3)) mean(atelier_med(:,4)) mean(atelier_med(:,5)) mean(atelier_med(:,6))];
mean_atelier_high = [mean(atelier_high(:,1)) mean(atelier_high(:,2)) mean(atelier_high(:,3)) mean(atelier_high(:,4)) mean(atelier_high(:,5)) mean(atelier_high(:,6))];

%% Plot atelier

figure;
tiledlayout(3,1);

%plot(x,atelier_low(1,:))

nexttile([1 1]);
b_atelier_low = bar(atelier_low);
%b_atelier_low.FaceColor = 'flat';
%b_atelier_low.CData(1,2) = [.5 0 .5];
%{
b_atelier_low.CData(2,:) = [0 0 1];
b_atelier_low.CData(3,:) = [0 1 0];
b_atelier_low.CData(4,:) = [1 1 0];
b_atelier_low.CData(5,:) = [1 .6471 0];
b_atelier_low.CData(6,:) = [1 0 0];
%}
title('atelier low');


nexttile([1 1]);
b_atelier_med = bar(atelier_med);
title('atelier medium');

nexttile([1 1]);
b_atelier_high = bar(atelier_high);
title('atelier high');

figure;
tiledlayout(3,1);

nexttile([1 1]);
b_mean_atelier_low = bar(mean_atelier_low);
title('atelier mean low');

nexttile([1 1]);
b_mean_atelier_med = bar(mean_atelier_med);
title('atelier mean med');
nexttile([1 1]);
b_mean_atelier_high = bar(mean_atelier_high);
title('atelier mean high');
