close all;
clear;
load data_set1.mat;
x = linspace(1,263,263);
figure;
plot(x,data_set_1(:,1),'r-*',x,data_set_1(:,2),'b-o')

title('Data Set 1');
xlabel('time');
ylabel('filtered / unfiltered signal');
legend('lpf signal','raw signal');
str1 = '3 bulbs in front of atelier door';
%a = annotation('textarrow',x,y,'String','y = x ');
%a1 = annotation('textarrow',40,800,'String',str1);