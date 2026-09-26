#include <stdio.h>
int main(){
	
	char c1;
	int c2;
	printf("Enter problem type, C for classification, R for regression, D for clustering, V for computer vision ");
	scanf(" %c", &c1);
	switch(c1){
		case 'C': 
		case 'c':
		        printf("enter 1 for Logistic Regression 2 for Decision Tree 3 for KNN");
		        scanf("%d", &c2);
		        switch(c2){
		        	case 1: printf("Classification: Logistic Regression ");
					break;
					case 2: printf("Classification: Decision Tree");
					break;
					case 3: printf("Classification: KNN");
					break;
					default: printf("invalid classification entered");
					}
					break;
				
		case 'V': 
		case 'v':
		        printf("enter 1 for CNN 2 for YOLO 3 for R-CNN ");
		        scanf("%d", &c2);
		        switch(c2){
		        	case 1: printf("Computer Vision-CNN");
					break;
					case 2: printf("Computer Vision-YOLO");
					break;
					case 3: printf("Computer Vision-R-CNN");
					break;
				    default: printf("invalid Computer Vision entered");
					}
						break;
				
		case 'R': 
		case 'r':
		        printf("enter 1 for Linear Regression 2 for Polynomial Regression 3 for SVR ");
		        scanf("%d", &c2);
		        switch(c2){
		        	case 1: printf("Regression-Linear Regression,");
					break;
					case 2: printf("Regression-Polynomial Regression");
					break;
					case 3: printf("Regression-SVR");
					break;
				    default: printf("invalid Regression entered");
					}
						break;
				
		case 'D':
		case 'd':
		        printf("enter 1 for K-Means 2 for Hierarchical Clustering 3 for DBSCAN ");
		        scanf("%d", &c2);
		        switch(c2){
		        	case 1: printf("Clustering-K-Means");
					break;
					case 2: printf("Clustering-Hierarchical Clustering");
					break;
					case 3: printf("Clustering-DBSCAN");
					break;
				    default: printf("invalid clustering entered");
					}
					break;
					default: printf("invalid problem type entered");
	}
		  return 0;      
	}
