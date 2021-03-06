#include "Matriz.hpp"

using namespace std;

//Implementaações classe matriz
bool controle(int a,int b,char modo){
	if(!(modo-'U'))
		return(a>b);
	else if(!(modo-'L'))
		return (a<b);
}

void Matriz::setLinhas(int l){
	linhas=l;
}

void Matriz::setColunas(int c){
	colunas=c;
}

int Matriz::getLinhas(void) const{
	return linhas;
}

int Matriz::getColunas(void) const{
	return colunas;
}

void Matriz::setElemento(const int linha,const int coluna,const double elemento){
	if(linha>=0 && linha<getLinhas() && coluna>=0 && coluna<getColunas())
		elementos[linha][coluna] = elemento;
	/*else
		cout<<"["<<l<<","<<c<<"]"<<"Posicao Invalida"<<endl;*/
}
double Matriz::getElemento(const int linha,const int coluna) const{
	if(linha>=0 && linha < getLinhas() && coluna>=0 && coluna < getColunas())
		return elementos[linha][coluna];
	/*else
	{
		cout<<"["<<l<<","<<c<<"]"<<"Posicao Invalida"<<endl;
		return 1;
	}*/
}

void Matriz::setB(int n,double valor){
	if(n>-1 && n<getLinhas())
		b[n]=valor;
	/*else
	cout<<"["<<n<<"]"<<"Possicao !Invalida"<<endl;*/
}

double Matriz::getB(int n){
	if(n>-1 && n<getLinhas())
		return b[n];
	/*else
	cout<<"["<<n<<"]"<<"Possicao!! Invalida"<<endl;*/
}

Matriz::Matriz(const int nLinhas, const int nColunas){
	int k;
	elementos = new double*[nLinhas];
	if(!elementos)
	{
		printf("Error pointer for pointer dinamic alocation");
		exit(0);
	}
	else{
		for(k=0; k < nLinhas;k++){
			elementos[k] = new double[nColunas];
				if(!(elementos[k])){
					printf("ERRO! Não foi possível alocar o vetor de elementos. (%d)",k+1);
					exit(1);
				}
		}
		setLinhas(nLinhas);
		setColunas(nColunas);
		b = new double[nLinhas];
		if (!b){
			cout<<"ERRO! Não foi possível alocar o vetor B."<<endl;
			exit(2);
		}
	}
}
/*
Matriz::Matriz(int n,float*x,float*y):Matriz(n,2)
{
	for(int c=0;c<n;c++)
	{
		setElemento(c,0,x[0]);
		setElemento(c,1,y[0]);
	}
}*/
Matriz::~Matriz(){
	int k;
	for(k=0;k<getLinhas();k++)
		delete[](elementos[k]);
	delete[] elementos;
	delete[] b;
}

void Matriz::imprimirMatriz(){
	int k,w;
		printf("\n");
		for(k=0;k<getLinhas();k++)
		{
			for(w=0;w<getColunas();w++)
			{
				printf(" %16.8lf",getElemento(k,w));
			}
			printf("  %16.8lf",getB(k));
		    printf("\n");
		}
		printf("\n");
}
void Matriz::setMatriz(){
	int k,w;
	double aux;

	for(k=0;k<getLinhas();k++)
		for(w=0;w<getColunas();w++)
		{
			printf("\nDigite o elemento [%d][%d]: ",k+1,w+1);
			scanf("%lf",&aux);
			setElemento(k,w,aux);
		}
}

void Matriz::setVetorB(void)
{
	for(int k=0;k<getLinhas();k++)
	{	double aux;
		cout<<"Digite o B["<<k<<"] = ";
		cin>>aux;
	 	setB(k,aux);
	}
}

void Matriz::trocaLinhas(int l1,int l2)
{
	double *aux,aux1;
	if(l1>=0 && l1<getLinhas() && l2>=0 && l2<getLinhas())
	{
		aux = elementos[l1];
		elementos[l1]=elementos[l2];
		elementos[l2]=aux;
		aux1=getB(l1);
		setB(l1,getB(l2));
		setB(l2,aux1);
		
	}
	else{
		//cout << "Operacao Invalida (AQUI MEMO)"<<endl;
	}
}

int * Matriz::fatoracaoLU(char modo,int *p)
{
	int l,c;
	double m;
	
	//cout<<endl<<"\tFATORACAO LU\t"<<endl;
	if(modo=='N')
		pivoteamento(&p,'E');
	else
		pivoteamento(&p,'V');
	
	if(p)
	{
		if(modo=='N')
		{
			for(c=0;c<getColunas();c++)
			{	
				for(l=c+1;l<getLinhas();l++)
				{
					m=(getElemento(l,c)/getElemento(c,c));
					setElemento(l,c,m);
					LmLY(l,c,m,'L');
				}
			}
		}
		//MostraSolucaoMatriz();
		resolveSistemaTriangular('L');
		//MostraSolucaoMatriz();
		resolveSistemaTriangular('U');
	}
	
	return p;
	
}
void Matriz::eliminacaoDeGauss(void)
{
	int l,c,*p= new int[getLinhas()];
	double m;
	cout<<endl<<"\tELIMINACAO GAUSSIANA\t"<<endl;
	pivoteamento(&p,'E');
	for(c=0;c<getColunas();c++)
	{	
		for(l=c+1;l<getLinhas();l++)
		{
			m=(getElemento(l,c)/getElemento(c,c));
			setElemento(l,c,0);
			LmLY(l,c,m,'E');
		}
	}
	imprimirMatriz();
	resolveSistemaTriangular('U');
	pivoteamento(&p,'S');
}
void Matriz::gaussJacobi(void)
{
	int m,i,j,l1=0,l2=0;
	double xk,menor,ERRO=10e-6;
	double *y,*x,*p;
	x= new double[getLinhas()];
	y=new double[getLinhas()];
	p= new double[getLinhas()];
	if(!y || !x || !p)
	{
		cout<<"ERRO!!";
		exit(5);
	}
	for(int k=0; k<getLinhas(); k++)
	{
			y[k]=getB(k);
			x[k]=0;
	}
	for(l1=0;l1<getLinhas() && alfa()>=1;l1++)
	{	
		for(l2=l1+1;l2<getLinhas() && alfa()>=1;l2++)
		{	
			if(getElemento(l2,l1)!=0)
			{
				trocaLinhas(l1,l2);
				if(alfa()>=1)//Nao funcionou a troca, volta
				trocaLinhas(l1,l2);
				else
				break;
			}
		}
		if(alfa()<1)
			break;
	}
	for(m=0,xk=1;xk>ERRO && m<100 ; m++)
	{
		for(i=0;i<getLinhas();i++)
			for(j=0;j<getLinhas();j++)
				if(i!=j)	
					x[i]-=getElemento(i,j)*x[j];
				
			
		

		for(i=0;i<getLinhas();i++)
		{
			x[i]/=getElemento(i,i);
			cout<<"X["<<i<<"]"<<" = "<<x[i]<<endl;
		}
		
		for(i=0;i<getLinhas();i++)
		{
			if((xk=fabs(y[i]-x[i])) < menor || !i)
					menor=xk;
			y[i]=x[i];
		
		}	 
	
	}

	for(int k=0; k<getLinhas(); k++)
		setB(k,x[k]);
	
	if(l1-l2)
	trocaLinhas(l1,l2);
}

double Matriz::alfa(void){
	double soma,maior;
 	int l,c;
	for(l=0;l<getLinhas();l++)
	{
		for(c=0,soma=-fabs(getElemento(l,l));c<getLinhas();c++)
			soma+=fabs(getElemento(l,c));
		soma/=fabs(getElemento(l,l));
		
			if(l==0 || soma> maior)
				maior=soma;
	
	}
 
 return maior;
}
void Matriz::LmLY(int l1,int l2,double m,char modo)//linha1 = linha1 - linha2 * m apartir de linha2+1
{
	int c;
	
	for(c=l2+1;c<getColunas();c++)
		setElemento(l1,c,(getElemento(l1,c)-m*getElemento(l2,c)));
	
	if(modo=='E')
		setB(l1,getB(l1)-m*getB(l2));//Isso não é necessário na LU!!!
	
	
	return;
}
void Matriz::resolveSistemaTriangular(char modo)
{
	int c,L,a;
	double *y;
	y= new double[getLinhas()];
	if(!y){
		cout<<"ERRO!!";
	}
	for(int k=0; k<getLinhas(); k++)
			y[k]=getB(k);
	
	if(!(modo-'U'))//Para sistema matriz UPPER
	{
		c = getLinhas()-1;
		L = -1;
		a=-1;
	}
	else
	if(!(modo-'L'))//Para sistema matriz LOWER
	{
		c = 0;
		L = getLinhas();
		a=1;
	}
	else
	{
		cout<<"ERRO!!";
	}
	
	
	for(;controle(c,L,modo);c+=a)
	{	double divisor = modo=='L'?1:getElemento(c,c);
		y[c]=(decressimoDoJaCalculado(c,y,modo))/divisor;/// X[c] = ( B[c] -(X[0]*A[c][0]+X[1]*A[c][1]+.....+X[c-1]*A[c][c-1]+X[c+1]*A[c][c+1]+......+X[n]*A[c][n]))/A[c][c]
		//cout<<"/"<<divisor;
		//cout<<endl;
	}

	
	for(int k=0; k<getLinhas(); k++)
			setB(k,y[k]);
	
	delete []y;
	
	return;
}
double Matriz::decressimoDoJaCalculado(int l,double *x,char modo)
{
	int c,L,a;
	double soma=0;
	
	if(!(modo-'U'))//Para sistemar matriz UPPER
	{
		c = getLinhas()-1;
		L = -1;
		a=-1;
		//cout<<"UPPER"<<endl;
	}
	else//Para sistema matriz LOWER
	{
		c = 0;
		L = getLinhas();
		a=1;
		//cout<<"LOWER"<<endl;
	}
	//cout <<x[l];
	for( ;controle(c,L,modo) && controle(c,l,modo);c+=a)
	{	
			soma+=x[c]*getElemento(l,c);
			//printf(" -%lf*%lf",x[c],getElemento(l,c));
	}
		
	
	return x[l]-soma;
	
}
void Matriz::mostraSolucaoMatriz(){
	for(int k=0;k<getLinhas();k++)
		printf("\n\tx[%d] = %10.8lf\t\n",k,getB(k));
}

void Matriz::pivoteamento(int **x,char modo){
	if(modo=='E'){
		int c,l,imaior;
	 	double maior;
		
		for(c=0,(*x)[getLinhas()-1]=1 ;c<getLinhas()-1; c++){
			maior = fabs(getElemento(c,c));
		 	imaior =c;
			for(l=c+1;l<getLinhas();l++)
			{	double atual=fabs(getElemento(l,c));
				//cout<<"Atual: "<<atual<<endl;
			 	if(maior < atual )
				{
						maior =atual;
						imaior=l;
				}
			}
				//cout<<"MAIOR: "<<maior<<endl;
				if(maior!= 0 && imaior != c)
				{
					trocaLinhas(c,imaior);
					//cout<<"\tEstado Atual\t"<<endl;
					//PrintMatriz();
					(*x)[c]=imaior;
					(*x)[getLinhas()-1]*=-1;
				}
				else
				if(maior==0)
				{
					cout<<"\tImpossivel Resolver por causa da coluna: "<<c<<"\t"<<endl;
					(*x)=NULL;
					return;
				}
				else
				{
					(*x)[c]=0;
				}
		}
	 
	 	//printf("VALOR DO ULTIMO:%d\n",(*x)[getLinhas()-1]);
				
	}else
	if(modo=='S')
	{	int c;
		for(c=getLinhas()-1;c>-1;c--)
		{
			if((*x)[c]!=0)
			{
				trocaLinhas(c,(*x)[c]);
			}
			if((*x)[getLinhas()-1]-1)
			{
				setB(c,-getB(c));
				cout<<"Inverteu!!!!"<<endl;
			}
		}
	}
	else
	if(modo=='V')
	{
		/*int c;
		for(c=getLinhas()-2;c>-1;c--)
		{
			if((*x)[c]!=0)
			{
				double aux;
				cout<<"TORCA "<<c<<" POR "<<(*x)[c]<<endl;
				aux=getB(c);
				setB(c,getB((*x)[c]));
				setB((*x)[c],aux);
			}
		}//*/
		
		int c;
		for(c=0;c<getLinhas()-1;c++)
		{
			if((*x)[c]!=0)
			{
				double aux;
				//cout<<"TORCA "<<c<<" POR "<<(*x)[c]<<endl;
				aux=getB(c);
				setB(c,getB((*x)[c]));
				setB((*x)[c],aux);
			}
		}//*/
	}
		
}
void Matriz::copiaMatriz(Matriz *a){
	Matriz *nova; 
	if(getColunas()==a->getColunas() && getLinhas()==a->getLinhas())
	{
		for(int c=0;c<a->getColunas();c++)
			for(int l=0;l<a->getLinhas();l++)
					setElemento(l,c,a->getElemento(l,c));
			for(int l=0;l<a->getLinhas();l++)
				setB(l,a->getB(l));

	}
	else
	{
		cout<<"Matrizes de tamanhos diferentes"<<endl;
		exit(4);
	}
}
void Matriz::copiaVetorMatriz(Matriz *a)
{
	Matriz *nova; 
	if(getColunas()==a->getColunas() && getLinhas()==a->getLinhas())
			for(int l=0;l<a->getLinhas();l++)
				setB(l,a->getB(l));
	else
	{
		cout<<"Matrizes de tamanhos diferentes"<<endl;
		exit(4);
	}
}
void Matriz::interpolar(Polinomio **px){
	if(getColunas()==2 && getLinhas() >0)
	{
		int c,c1,*p = new int[getLinhas()];
		Matriz aux(getLinhas(),getLinhas());
		
		for(c=0;c<getLinhas();c++)
		{	
			aux.setElemento(c,0,1);
		
			for(c1=1;c1<getLinhas();c1++)
				aux.setElemento(c,c1,pow(getElemento(c,0),c1));

			aux.b[c]=getElemento(c,1);
		}
	 
	 	p=aux.fatoracaoLU('N',p);
	 
	 	if (*px != NULL)
	 		delete (*px);
	 	*px = new Polinomio(getLinhas()-1);
	 	if (*px == NULL){
	 		cout << "ERRO! Não foi possível alocar o polinômio." << endl;
	 		exit(1);
	 	}
	 	for(c=0;c<getLinhas();c++)
	 		(*px)->setCoeficiente(c,aux.b[c]);
			
	}
}
