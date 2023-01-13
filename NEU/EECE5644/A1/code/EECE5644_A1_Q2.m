
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
%EECE5644 Sprint 2022
%Homework #1
%Problem #2
%Significant parts of this code were derived from the following sources 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 

clear all;
close all;

N = 10000; %number of samples
n = 3; %number of dimensions
C = 3; %number of classes

p = [0.3, 0.3, 0.4]; %class priors

%class conditional distributions
sigma(:,:,1) = [rand 0 0
                0 rand 0
                0 0 rand];
sigma(:,:,2) = [rand 0 0
                0 rand 0
                0 0 rand];
sigma(:,:,3) = [rand 0 0
                0 rand 0
                0 0 rand];
sigma(:,:,4) = [rand 0 0
                0 rand 0
                0 0 rand];

averageStdDev = trace(sum(sqrt(sigma),3))/16; %offset means by 2 std devs

mu(:,1) = [0; 0; 0];
mu(:,2) = [2*averageStdDev; 0; 0];
mu(:,3) = [averageStdDev; averageStdDev*sqrt(3); 0];
mu(:,4) = [averageStdDev; averageStdDev*(sqrt(3)/3); averageStdDev*sqrt(8/3)];

% Data generation and labelling
label = rand(1,N);
for i = 1:length(label)
    if label(i) < p(1)
        label(i) = 1;
    elseif label(i) < (p(2)+p(1))
        label(i) = 2;
    elseif label(i) < ((p(3)/2)+p(2)+p(1)) %two subclasses for the last class, will be combined later
        label(i) = 3;
    else
        label(i) = 4;
    end 
end

NumClass = [sum(label==1),sum(label==2),sum(label==3),sum(label==4)];
x = zeros(n,N);
x(:, label==1) = mvnrnd(mu(:,1), sigma(:,:,1),  NumClass(1))';
x(:, label==2) = mvnrnd(mu(:,2), sigma(:,:,2),  NumClass(2))';
x(:, label==3) = mvnrnd(mu(:,3), sigma(:,:,3),  NumClass(3))';
x(:, label==4) = mvnrnd(mu(:,4), sigma(:,:,4),  NumClass(4))';

% Combine labels 2 and 3 into one class under label 2
for i = 1:length(label)
    if label(i) == 4
        label(i) = 3;
    end 
end
NumClass = [sum(label==1),sum(label==2),sum(label==3)];

% plot generated data
figure
scatter3(x(1, label==1),x(2, label==1),x(3, label==1),'bo')
hold on
scatter3(x(1, label==2),x(2, label==2),x(3, label==2),'r*')
scatter3(x(1, label==3),x(2, label==3),x(3, label==3),'gx')
title('True Data Distributions')
legend('Class 1','Class 2','Class 3')
xlabel('x1')
ylabel('x2')
zlabel('x3')
hold off

%% Part A - MAP Classifier with True Knowledge

% Evaluate class conditional pdfs
pxgivenl(1,:) = mvnpdf(x', mu(:,1)', sigma(:,:,1))';
pxgivenl(2,:) = mvnpdf(x', mu(:,2)', sigma(:,:,2))';
pxgivenl(3,:) = .5*mvnpdf(x', mu(:,3)', sigma(:,:,3))' + .5*mvnpdf(x', mu(:,4)',sigma(:,:,4))'; %two distributions for class 3

% Find class posteriors
px = p*pxgivenl; %total probability
plgivenx = pxgivenl.*repmat(p',1,N)./repmat(px,C,1); %class posterior functions

% Loss matrix, 0-1 loss provides minimum probability of error
lossMatrix = ones(3,3)-eye(3);
expectedRisks = lossMatrix*plgivenx;
[~,decisions] = min(expectedRisks,[],1);

% Make confusion matrix and plot data
figure
shapes = ['o','*','x'];
for i = 1:C %each decision
    for j = 1:C %each class label
        confusionMatrix(i,j) = sum(decisions==i & label==j)/NumClass(j);
        if i == j
            scatter(i,j) = scatter3(x(1,decisions==i & label==j), ...
                x(2,decisions==i & label==j), ...
                x(3,decisions==i & label==j), ...
                'g',shapes(j), ...
                'DisplayName', ...
                ['Class ' num2str(j) ' Correct Classification']);
            hold on 
        else
            scatter(i,j) = scatter3(x(1,decisions==i & label==j), ...
                x(2,decisions==i & label==j), ...
                x(3,decisions==i & label==j), ...
                'r',shapes(j), ...
                'DisplayName', ...
                ['Class ' num2str(j) ' Incorrect Classification']);
            hold on 
        end
    end 
end
title('Correct vs. Incorrect Classification')
legend([scatter(1,1) scatter(2,1) scatter(2,2) scatter(3,2) scatter(3,3) scatter(1,3)])
xlabel('x1')
ylabel('x2')
zlabel('x3')
hold off

%% higher loss

% Loss matrix, Lambda_10
lossMatrix10 = [0 1 10
                1 0 10
                1 1 0];
expectedRisks10 = lossMatrix10*plgivenx;
[~,decisions10] = min(expectedRisks10,[],1);

% Make confusion matrix and plot data
figure
for i = 1:C %each decision
    for j = 1:C %each class label
        confusionMatrix10(i,j) = sum(decisions10==i & label==j)/NumClass(j);
        if i == j
            scatter(i,j) = scatter3(x(1,decisions10==i & label==j),...
            x(2,decisions10==i & label==j), ...
            x(3,decisions10==i & label==j), ...
            'g',shapes(j),'DisplayName', ...
            ['Class ' num2str(j) ' Correct Classification']);
            hold on 
        else
            scatter(i,j) = scatter3(x(1,decisions10==i & label==j),...
            x(2,decisions10==i & label==j), ...
            x(3,decisions10==i & label==j), ...
            'r',shapes(j),'DisplayName', ...
            ['Class ' num2str(j) ' Incorrect Classification']);
            hold on 
        end
    end 
end
title('Correct vs. Incorrect Classification (Lambda=10)')
legend([scatter(1,1) scatter(2,1) scatter(2,2) scatter(3,2) scatter(3,3) scatter(1,3)])
xlabel('x1')
ylabel('x2')
zlabel('x3')
hold off

% Loss matrix, Lambda_100
lossMatrix100 = [0 1 100
                1 0 100
                1 1 0];
expectedRisks100 = lossMatrix100*plgivenx;
[~,decisions100] = min(expectedRisks100,[],1);

% Make confusion matrix and plot data
figure
for i = 1:C %each decision
    for j = 1:C %each class label
        confusionMatrix100(i,j) = sum(decisions100==i & label==j)/NumClass(j);
        if i == j
            scatter(i,j) = scatter3(x(1,decisions100==i & label==j),...
            x(2,decisions100==i & label==j),...
            x(3,decisions100==i & label==j), ...
            'g',shapes(j),'DisplayName', ...
            ['Class ' num2str(j) ' Correct Classification']);
            hold on 
        else
            scatter(i,j) = scatter3(x(1,decisions100==i & label==j),...
            x(2,decisions100==i & label==j),...
            x(3,decisions100==i & label==j), ...
            'r',shapes(j),'DisplayName', ...
            ['Class ' num2str(j) ' Incorrect Classification']);
            hold on 
        end
    end 
end
title('Correct vs. Incorrect Classification (Lambda=100)')
legend([scatter(1,1) scatter(2,1) scatter(2,2) scatter(3,2) scatter(3,3) scatter(1,3)])
xlabel('x1')
ylabel('x2')
zlabel('x3')
hold off


