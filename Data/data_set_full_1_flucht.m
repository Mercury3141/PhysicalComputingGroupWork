close all;
clear;
load data_set_full_1.mat;
x = linspace(1,6,6);

%% Calculate Means
mean_flucht_low = [mean(flucht_low(:,1)) mean(flucht_low(:,2)) mean(flucht_low(:,3)) mean(flucht_low(:,4)) mean(flucht_low(:,5)) mean(flucht_low(:,6))];
mean_flucht_med = [mean(flucht_med(:,1)) mean(flucht_med(:,2)) mean(flucht_med(:,3)) mean(flucht_med(:,4)) mean(flucht_med(:,5)) mean(flucht_med(:,6))];
mean_flucht_high = [mean(flucht_high(:,1)) mean(flucht_high(:,2)) mean(flucht_high(:,3)) mean(flucht_high(:,4)) mean(flucht_high(:,5)) mean(flucht_high(:,6))];

%% Plot flucht

figure;
tiledlayout(3,1);

%plot(x,flucht_low(1,:))

nexttile([1 1]);
b_flucht_low = bar(flucht_low);
%b_flucht_low.FaceColor = 'flat';
%b_flucht_low.CData(1,2) = [.5 0 .5];
%{
b_flucht_low.CData(2,:) = [0 0 1];
b_flucht_low.CData(3,:) = [0 1 0];
b_flucht_low.CData(4,:) = [1 1 0];
b_flucht_low.CData(5,:) = [1 .6471 0];
b_flucht_low.CData(6,:) = [1 0 0];
%}
title('flucht low');


nexttile([1 1]);
b_flucht_med = bar(flucht_med);
title('flucht medium');

nexttile([1 1]);
b_flucht_high = bar(flucht_high);
title('flucht high');

figure;
tiledlayout(3,1);

nexttile([1 1]);
b_mean_flucht_low = bar(mean_flucht_low);
title('flucht mean low');

nexttile([1 1]);
b_mean_flucht_med = bar(mean_flucht_med);
title('flucht mean med');
nexttile([1 1]);
b_mean_flucht_high = bar(mean_flucht_high);
title('flucht mean high');
