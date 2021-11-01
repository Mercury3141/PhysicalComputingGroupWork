close all;
clear;
load data_set_full_1.mat;
x = linspace(1,6,6);

%% Calculate Means
mean_cast_low = [mean(cast_low(:,1)) mean(cast_low(:,2)) mean(cast_low(:,3)) mean(cast_low(:,4)) mean(cast_low(:,5)) mean(cast_low(:,6))];
mean_cast_med = [mean(cast_med(:,1)) mean(cast_med(:,2)) mean(cast_med(:,3)) mean(cast_med(:,4)) mean(cast_med(:,5)) mean(cast_med(:,6))];
mean_cast_high = [mean(cast_high(:,1)) mean(cast_high(:,2)) mean(cast_high(:,3)) mean(cast_high(:,4)) mean(cast_high(:,5)) mean(cast_high(:,6))];

%% Plot Cast

figure;
tiledlayout(3,1);

%plot(x,cast_low(1,:))

nexttile([1 1]);
b_cast_low = bar(cast_low);
%b_cast_low.FaceColor = 'flat';
%b_cast_low.CData(1,2) = [.5 0 .5];
%{
b_cast_low.CData(2,:) = [0 0 1];
b_cast_low.CData(3,:) = [0 1 0];
b_cast_low.CData(4,:) = [1 1 0];
b_cast_low.CData(5,:) = [1 .6471 0];
b_cast_low.CData(6,:) = [1 0 0];
%}
title('cast low');


nexttile([1 1]);
b_cast_med = bar(cast_med);
title('cast medium');

nexttile([1 1]);
b_cast_high = bar(cast_high);
title('cast high');

figure;
tiledlayout(3,1);

nexttile([1 1]);
b_mean_cast_low = bar(mean_cast_low);
title('cast mean low');

nexttile([1 1]);
b_mean_cast_med = bar(mean_cast_med);
title('cast mean med');
nexttile([1 1]);
b_mean_cast_med = bar(mean_cast_high);
title('cast mean high');
