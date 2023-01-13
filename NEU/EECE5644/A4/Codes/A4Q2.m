%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%EECE5644 Spring 2022
%Homework #4
%Problem #2
%Significant parts of this code were derived from the following sources 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if 1 %Set to 0 to just plot existing data
clear all;
close all;
warning off;

%Input data
filenames = {'surf.jpg'}; 
dTypes={'surfing'};

%Cross validation parameters 
NumGMMtoCheck=10; 
k=10;
end

for ind=1:length(filenames)
    imdata = imread(filenames{ind}); 
    figure(1); 
    subplot(length(filenames),3,(ind-1)*3+1); 
    imshow(imdata);
    
    if 0 %Skip pre-processing and GMM=2 evaluation 
    %Flatten into num features x number of normalized points
    [R,C,D]=size(imdata); 
    N=R*C; 
    imdata=double(imdata);

    rows=(1:R)'*ones(1,C); 
    columns=ones(R,1)*(1:C); 
    featureData=[rows(:)';columns(:)'];

    for ind2=1:D
        imdatad=imdata(:,:,ind2); 
        featureData=[featureData; imdatad(:)'];
    end

    minf=min(featureData,[],2); 
    maxf=max(featureData,[],2); 
    ranges=maxf-minf;

    %Normalization
    x=(featureData-minf)./ranges;

    %Assess GMM with 2 Gaussians case
    GMM2=fitgmdist(x',2,'Replicates',10); 
    post2=posterior(GMM2,x')'; 
    decisions=post2(2,:)>post2(1,:);
    end

    %Plot GMM=2 case
    labelImage2=reshape(decisions,R,C); 
    subplot(length(filenames),3,(ind-1)*3+2); 
    imshow(uint8(labelImage2*255/2));

    if 0 %Skip k-fold evaluation and training 
    %Perform k-fold cross-validation to determine optimal number of Gaussians for GMM model
    N=length(x); 
    numValIters=10;

    %Setup cross validation on training data
    partSize=floor(N/k); 
    partInd=[1:partSize:N length(x)];

    %Perform cross validation
    % select number of perceptrons
    for NumGMMs=1:NumGMMtoCheck 
        for NumKs=1:k
            index.val=partInd(NumKs):partInd(NumKs+1); 
            index.train=setdiff(1:N,index.val);
            %Create object with M perceptrons in hidden layer
            GMMk_loop=fitgmdist(x(:,index.train)',NumGMMs, 'Replicates',5);

            if GMMk_loop.Converged 
                probX(NumKs)=sum(log(pdf(GMMk_loop,x(:,index.val)')));
            else
                probX(NumKs)=0;
            end 
        end
        %Determine average probability of error
        avgProb(ind,NumGMMs)=mean(probX); 
        stats(ind).NumGMMs=1:NumGMMtoCheck; 
        stats(ind).avgProb=avgProb; 
        stats(ind).mProb(:,NumGMMs)=probX;
        fprintf('File: %1.0f, NumGMM: %1.0f\n',ind,NumGMMs);
    end
    end

    %Select GMM with maximum probability 
    [~,optNumGMM]=max(avgProb(ind,:)); 

    %optNumGMM=3; 
    GMMk=fitgmdist(x',optNumGMM,'Replicates',10); 
    postk=posterior(GMMk,x')';
    lossMatrix=ones(optNumGMM,optNumGMM)-eye(optNumGMM);
    
    % Expected Risk for each label (rows) of each sample (columns)
    expectedRisks =lossMatrix*postk; 

    % Minimum expected risk decision with 0-1 loss 
    % Same as MAP
    [~,decisions] = min(expectedRisks,[],1); 

    %Plot segmented image for Max. Likelihood number of GMMs case
    labelImageK=reshape(decisions-1,R,C); 
    subplot(length(filenames),3,(ind-1)*3+3); 
    imshow(uint8(labelImageK*255/optNumGMM));

    save(['HW4_Q2' num2str(ind) '.mat']);
end
