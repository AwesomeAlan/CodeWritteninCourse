%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
%EECE5644 Spring 2022
%Homework #1
%Problem #3B
%Significant parts of this code were derived from the following sources 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
%% Human Activity Dataset Class Conditional/Prior Estimation
clear all;
close all;
%% 

% import data from excel
x_test = readmatrix('X_test.txt', 'Range', 'B2:UP2948')';
x_train = readmatrix('X_train.txt', 'Range', 'B2:UP7353')';
label_test = readmatrix('y_test', 'Range', 'A2:A2948')';
label_train = readmatrix('y_train', 'Range', 'A2:A7353')';
x = horzcat(x_test,x_train);
label = horzcat(label_test,label_train);
N = size(x,2); %number of samples
n = size(x,1); %number of dimensions
C = 6; %number of classes
%% 

alpha = 0.1; %for regularization
sigmaTotal = cov(x'); %for regularization

% Estimate class conditionals (gaussian) and class priors
for i = 1:C
    % estimate class prior
    p(i) = sum(label==i)/N;
    % estimate mean
    mu(:,i) = mean(x(:,label==i),2);
    % estimate covariance matrix
    sigma(:,:,i) = cov(x(:,label==i)');
    % regularize covariance matrix
    sigma(:,:,i) = sigma(:,:,i) + eye(size(sigma,1))*alpha*trace(sigmaTotal)/rank(sigmaTotal);
end

%% Human Activity Dataset ERM
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

% Total error probability estimate
countError = sum(label~=decisions);
pE = countError/N;

% Make confusion matrix
for i = 1:C %each decision
    for j = 1:C %each class label
        if sum(isnan(sigma(:,:,j)))==0
            confusionMatrix(i,j) = sum(decisions==i & label==j)/sum(label==j);
        else
            confusionMatrix(i,j) = 0;
        end 
    end
end

%% Human Activity Dataset PCA and Plotting
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

% Calculate the first three principal components for visualization
y = Q(:,1:3)'*xzm;

% Percent of variance maintained
percentVar = trace(D(1:3,1:3))/trace(D);

% Plot data after PCA
figure
scatter3(y(1,label==1),y(2,label==1),y(3,label==1),'b*','DisplayName','Class 1')
hold on
scatter3(y(1,label==2),y(2,label==2),y(3,label==2),'g*','DisplayName','Class 2')
scatter3(y(1,label==3),y(2,label==3),y(3,label==3),'m*','DisplayName','Class 3')
scatter3(y(1,label==4),y(2,label==4),y(3,label==4),'c*','DisplayName','Class 4')
scatter3(y(1,label==5),y(2,label==5),y(3,label==5),'r*','DisplayName','Class 5')
scatter3(y(1,label==6),y(2,label==6),y(3,label==6),'k*','DisplayName','Class 6')
title('PCA on Human Activity Dataset')
xlabel('y1')
ylabel('y2')
zlabel('y3')
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