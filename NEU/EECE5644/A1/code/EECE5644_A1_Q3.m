%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
%EECE5644 Spring 2022
%Homework #1
%Problem #3A
%Significant parts of this code were derived from the following sources 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 

%% Wine Dataset Class Conditional/Prior Estimation
clear all;
close all;
%%
% import data from excel
x = readmatrix('winequality-white.csv', 'Range', 'A2:K4899')';
label = readmatrix('winequality-white.csv', 'Range', 'L2:L4899')';
%% 

N = size(x,2); %number of samples
n = size(x,1); %number of dimensions
C = 11; %number of classes
alpha = 0.1; %for regularization
sigmaTotal = cov(x'); %for regularization
%% 

% Estimate class conditionals (gaussian) and class priors
for i = 1:C
    % estimate class prior
    p(i) = sum(label==i-1)/N;
    % estimate mean
    mu(:,i) = mean(x(:,label==i-1),2);
    % estimate covariance matrix
    sigma(:,:,i) = cov(x(:,label==i-1)');
    % regularize covariance matrix
    sigma(:,:,i) = sigma(:,:,i) + eye(size(sigma,1))*alpha*trace(sigmaTotal)/rank(sigmaTotal);
end

%% Wine Dataset ERM
% Evaluate class conditional pdfs
for i = 1:C
    if sum(isnan(sigma(:,:,i)))==0
        pxgivenl(i,:) = mvnpdf(x', mu(:,i)', sigma(:,:,i))';
    else
        pxgivenl(i,:) = zeros(1,4898); %zero for classes without data
    end
end

% Find class posteriors
px = p*pxgivenl; %total probability
plgivenx = pxgivenl.*repmat(p',1,N)./repmat(px,C,1); %class posterior functions

% Loss matrix, 0-1 loss provides minimum probability of error
lossMatrix = ones(C,C)-eye(C);
expectedRisks = lossMatrix*plgivenx;
[~,decisions] = min(expectedRisks,[],1);
decisions = decisions-1; %because classes start at 0

% Total error probability estimate
countError = sum(label~=decisions);
pE = countError/N;

% Make confusion matrix
for i = 1:C %each decision
    for j = 1:C %each class label
        if sum(isnan(sigma(:,:,j)))==0
            confusionMatrix(i,j) = sum(decisions==i-1 & label==j-1)/sum(label==j-1);
        else
            confusionMatrix(i,j) = 0;
        end 
    end
end

%% Wine Dataset PCA and Plotting
% Without classes, sample based estimates of distribution (gaussian)
muHat = mean(x,2);
% sigmaTotal is calculated above
% Make data zero-mean
xzm = x - muHat*ones(1,N);

% Get and sort eignvalues/eigenvectors
[Q,D] = eig(sigmaTotal);
[d,ind] = sort(diag(D),'descend');
Q = Q(:,ind);
D = diag(d);

% Calculate the first two principal components for visualization
y = Q(:,1:2)'*xzm;

% Percent of variance maintained
percentVar = trace(D(1:2,1:2))/trace(D);

% Plot data after PCA
figure
hold on
plot(y(1,label==3),y(2,label==3),'g*','DisplayName','Class 3')
plot(y(1,label==4),y(2,label==4),'m*','DisplayName','Class 4')
plot(y(1,label==5),y(2,label==5),'c*','DisplayName','Class 5')
plot(y(1,label==6),y(2,label==6),'r*','DisplayName','Class 6')
plot(y(1,label==7),y(2,label==7),'y*','DisplayName','Class 7')
plot(y(1,label==8),y(2,label==8),'b*','DisplayName','Class 8')
plot(y(1,label==9),y(2,label==9),'k*','DisplayName','Class 9')
title('PCA on Wine Dataset')
xlabel('y1')
ylabel('y2')
legend
hold off

% Average distance between means and average standard deviation
counterDist = 0;
counterSig = 0;
for i = 1:C
    if sum(isnan(sigma(:,:,i)))==0
        counterSig = counterSig+1;
        standardDev(i) = trace(sqrt(sigma(:,:,i)))/size(sigma,1);
    end
    for j = 1:C
        if sum(isnan(sigma(:,:,j)))==0
            if i < j
                counterDist = counterDist+1;
                distances(i) = sqrt(sum((x(:,i)-x(:,j)).^2));
            end 
        end
    end 
end
averageDistance = sum(distances)/counterDist;
averageStdDev = sum(standardDev)/counterSig;