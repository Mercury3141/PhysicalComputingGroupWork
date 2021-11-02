close all;
clear;
load data_set_full_1.mat;
x = linspace(1,6,6);

%% Calculate Means
mean_stair_low = [mean(stair_low(:,1)) mean(stair_low(:,2)) mean(stair_low(:,3)) mean(stair_low(:,4)) mean(stair_low(:,5)) mean(stair_low(:,6))];
mean_stair_med = [mean(stair_med(:,1)) mean(stair_med(:,2)) mean(stair_med(:,3)) mean(stair_med(:,4)) mean(stair_med(:,5)) mean(stair_med(:,6))];
mean_stair_high = [mean(stair_high(:,1)) mean(stair_high(:,2)) mean(stair_high(:,3)) mean(stair_high(:,4)) mean(stair_high(:,5)) mean(stair_high(:,6))];

%% Plot stair

figure;
tiledlayout(3,1);

%plot(x,stair_low(1,:))

nexttile([1 1]);
b_stair_low = bar(stair_low);
%b_stair_low.FaceColor = 'flat';
%b_stair_low.CData(1,2) = [.5 0 .5];
%{
b_stair_low.CData(2,:) = [0 0 1];
b_stair_low.CData(3,:) = [0 1 0];
b_stair_low.CData(4,:) = [1 1 0];
b_stair_low.CData(5,:) = [1 .6471 0];
b_stair_low.CData(6,:) = [1 0 0];
%}
title('stair low');


nexttile([1 1]);
b_stair_med = bar(stair_med);
title('stair medium');

nexttile([1 1]);
b_stair_high = bar(stair_high);
title('stair high');

figure;
tiledlayout(3,1);

nexttile([1 1]);
b_mean_stair_low = bar(mean_stair_low);
title('stair mean low');

nexttile([1 1]);
b_mean_stair_med = bar(mean_stair_med);
title('stair mean med');
nexttile([1 1]);
b_mean_stair_high = bar(mean_stair_high);
title('stair mean high');
