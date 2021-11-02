close all;
clear;
load data_set_full_1.mat;
x = linspace(1,6,6);

%% Calculate Means
mean_out_low = [mean(out_low(:,1)) mean(out_low(:,2)) mean(out_low(:,3)) mean(out_low(:,4)) mean(out_low(:,5)) mean(out_low(:,6))];
mean_out_med = [mean(out_med(:,1)) mean(out_med(:,2)) mean(out_med(:,3)) mean(out_med(:,4)) mean(out_med(:,5)) mean(out_med(:,6))];
mean_out_high = [mean(out_high(:,1)) mean(out_high(:,2)) mean(out_high(:,3)) mean(out_high(:,4)) mean(out_high(:,5)) mean(out_high(:,6))];

%% Plot out

figure;
tiledlayout(3,1);

%plot(x,out_low(1,:))

nexttile([1 1]);
b_out_low = bar(out_low);
%b_out_low.FaceColor = 'flat';
%b_out_low.CData(1,2) = [.5 0 .5];
%{
b_out_low.CData(2,:) = [0 0 1];
b_out_low.CData(3,:) = [0 1 0];
b_out_low.CData(4,:) = [1 1 0];
b_out_low.CData(5,:) = [1 .6471 0];
b_out_low.CData(6,:) = [1 0 0];
%}
title('out low');


nexttile([1 1]);
b_out_med = bar(out_med);
title('out medium');

nexttile([1 1]);
b_out_high = bar(out_high);
title('out high');

figure;
tiledlayout(3,1);

nexttile([1 1]);
b_mean_out_low = bar(mean_out_low);
title('out mean low');

nexttile([1 1]);
b_mean_out_med = bar(mean_out_med);
title('out mean med');
nexttile([1 1]);
b_mean_out_high = bar(mean_out_high);
title('out mean high');
