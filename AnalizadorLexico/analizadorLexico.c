 * ********** Inclusi�n de cabecera ************* * /
# incluye  " anlex.h "

/ * ************ Variables globales ************* * /
ficha t;				             // token global para recibir componentes del Analizador Lexico

/ * **** Variables para el analizador lexico **** * /

ARCHIVO * archivo, * salida;               // Fuente JSON
id de char [TAMLEX];		                  // Utilizado por el analizador lexico
int numLinea = 1 ;			                  // Numero de Linea
char cont_esp [TAMESP];                // Variable para contar la cantidad de espacio
int con = - 1 ;                           // Variable que indica la cantidad de espacio que ya se ha cargado en cont_esp

/ * *************** Funciones ********************* * /
 error nulo ( const  char * mensaje)
{
	fprintf (salida, " Lin % d : Error Lexico. % s " , numLinea, mensaje);	
}

vac�o  sigLex ()
{
    int i = 0 ;
    char c = 0 ;
    int ban = 0 ;
    int acepto = 0 ;
	  int estado = 0 ;
	  char msg [ 41 ];
	  char aux [TAMAUX] = "  " ;
	  con = - 1 ;
	  ficha e;
     
   	while ((c = fgetc (archivo))! = EOF)
	  {
        if (c == ' \ n ' )
	      {
		        numLinea ++;
            fprintf (salida, " \ n " );
		        continuar ;
	       }
	      m�s  si (c == '  ' )
	      {
            hacer
            {
                // se encarga de cargar los espacios leidos para luego imprimirlos
                con ++;
                cont_esp [con] = '  ' ;
                c = fgetc (archivo);
            } while (c == '  ' );
            c = ungetc (c, archivo);
	       }
        m�s  si (c == ' \ t ' )
        { 
            // si es un tabulador que guarda los 4 espacios correspondientes
            while (c == ' \ t ' )
            { 
                fprintf (salida, " % c " , c);
	            	c = fgetc (archivo);
            }
         }
    	  m�s  si ( isdigit (c))
	      {
            // es un numero
            i = 0 ;
            estado = 0 ;
            acepto = 0 ;
            id [i] = c;
			      mientras que (! acepto)
			      {
				       interruptor (estado)
				       {
				           caso  0 : // una secuencia netamente de digitos, puede ocurrir. oe
						           c = fgetc (archivo);
						           si ( isdigit (c))
						           {
							             id [++ i] = c;
							             estado = 0 ;
						            }
						           m�s  si (c == ' . ' )
						           {
							             id [++ i] = c;
							             estado = 1 ;
						            }
						            otra cosa  si ( tolower (c) == ' e ' )
						            {
							             id [++ i] = c;
							             estado = 3 ;
						            }
						            m�s
							             estado = 6 ;
						            romper ;		
					          caso  1 : // un punto, debe seguir un digito
						            c = fgetc (archivo);						
						            si ( isdigit (c))
						            {
							              id [++ i] = c;
							              estado = 2 ;
						             }
						             m�s
                         {
							              fprintf (salida, " % s  % s  % c " , msg, " No se esperaba ' % c ' despues del. " , c);
							              estado = - 1 ;
						             }
						             romper ;
					           caso  2 : // la fraccion decimal, pueden seguir los digitos oe
						             c = fgetc (archivo);
						             si ( isdigit (c))
						             {
							               id [++ i] = c;
							               estado = 2 ;
						              }
						              otra cosa  si ( tolower (c) == ' e ' )
						              {
							               id [++ i] = c;
							               estado = 3 ;
						               }
						              m�s
							               estado = 6 ;
						              romper ;
					            caso  3 : // una e, puede seguir +, - o una secuencia de digitos
						              c = fgetc (archivo);
						              if (c == ' + ' || c == ' - ' )
						              {
							                id [++ i] = c;
							                estado = 4 ;
						               }
						              m�s  si ( isdigit (c))
						              {
							                id [++ i] = c;
							                estado = 5 ;
						               }
						               m�s
						              {
							                fprintf (salida, " % s  % s " , msg, " Se esperaba signo o digitos despues del exponente " );
							                estado = - 1 ;
						               }
						              romper ;
					            caso  4 : // problemas obligatorios por lo menos un digito
						              c = fgetc (archivo);
						              si ( isdigit (c))
						              {
							                id [++ i] = c;
							                estado = 5 ;
						               }
						              m�s
						              {
							                fprintf (salida, " % s  % s  % c " , msg, " No se esperaba ' % c ' despues del signo " , c);
							                estado = - 1 ;
						              }
						              romper ;
					            caso  5 : // una secuencia de d�gitos correspondiente al exponente
						              c = fgetc (archivo);
						              si ( isdigit (c))
						              {
							               id [++ i] = c;
							               estado = 5 ;
						              } 
						              m�s
							               estado = 6 ;
						              romper ;
					            caso  6 : // estado de aceptaci�n, devolver el caracter correspondiente a otro componente lexico
						              si (c! = EOF)
							                ungetc (c, archivo);
						              m�s
                              c = 0 ;
						              id [++ i] = ' \ 0 ' ;
						              acepto = 1 ;
                          t. compLex = N�MERO;
						              strcpy (t. lexema , id);
						              romper ;
					            caso - 1 :
						              si (c == EOF)
                             error ( " No se esperaba el fin de archivo \ n " );
						              m�s
                             error (msg);
                          acepto = 1 ;
                          t. compLex = VACIO;
                          while (c! = ' \ n ' )
                              c = fgetc (archivo);
                          ungetc (c, archivo);
					                romper ;
				         }
			       }
			       romper ;
		    }
        m�s  si (c == ' \ " ' )
		    {
            // un caracter o una cadena de caracteres
			     i = 0 ;
			     id [i] = c;
			     i ++;
			     hacer
			     {
				       c = fgetc (archivo);
				       if (c == ' \ " ' )
				       {
                    id [i] = c;
                    i ++;
                    prohibici�n = 1 ;
                    romper ;
				        }
               m�s  si (c == EOF || c == ' , ' || c == ' \ n ' || c == ' : ' )
				       {
                    fprintf (salida, " % s  % s " , msg, " Se esperaba que finalize el literal " );
					          error (msg);
                    
                    while (c! = ' \ n ' )
                        c = fgetc (archivo);

                    ungetc (c, archivo);
                    con = - 1 ;
                    romper ;                       
				       }
				       m�s
				       {
					          id [i] = c;
					          i ++;
				        }
			     } while ( isascii (c) || ??ban == 0 );
			     id [i] = ' \ 0 ' ;
           strcpy (t. lexema , id);
			     t. compLex = STRING;
			     romper ;
		  }
		  m�s  si (c == ' : ' )
		  {
            // puede ser un:
            t. compLex = DOS_PUNTOS;
            strcpy (t. lexema , " : " );
            romper ;
		   }
		  m�s  si (c == ' , ' )
		  {
			     t. compLex = COMA;
			     strcpy (t. lexema , " , " );
			     romper ;
		  }
		  m�s  si (c == ' [ ' )
		  {
			    t. compLex = L_CORCHETE;
			    strcpy (t. lexema , " [ " );
			    romper ;
		  }
		  m�s  si (c == ' ] ' )
		  {
			    t. compLex = R_CORCHETE;
			    strcpy (t. lexema , " ] " );
			    romper ;
		  }
		  m�s  si (c == ' { ' )
		  {
			    t. compLex = L_LLAVE;
			    strcpy (t. lexema , " { " );
			    romper ;		
       }
      otra cosa  si (c == ' } ' )
		  {
			    t. compLex = R_LLAVE;
			    strcpy (t. lexema , " } " );                        
			    romper ;		
       }
		  m�s  si (c == ' n ' || c == ' N ' )
      {
          ungetc (c, archivo);
          fgets (aux, 5 , archivo); // ver si es nulo
          if ( strcmp (aux, " null " ) == 0 || strcmp (aux, " NULL " ) == 0 )
          {
              t. compLex = PR_NULL;
              strcpy (t. lexema , aux);
           }
          m�s
          {
              fprintf (salida, " % s  % s  % c " , msg, " % c no esperado " , c);
			        error (msg);

              while (c! = ' \ n ' )
                  c = fgetc (archivo);

              t. compLex = VACIO;
              ungetc (c, archivo);
           }
          romper ;
       }   
       m�s  si (c == ' f ' || c == ' F ' )
       {
           ungetc (c, archivo);
           fgets (aux, 6 , archivo); // ver si es nulo
           if ( strcmp (aux, " false " ) == 0 || strcmp (aux, " FALSE " ) == 0 )
           {
                t. compLex = PR_FALSE;
                strcpy (t. lexema , aux);
            }
            m�s
            {
                fprintf (salida, " % s  % s  % c " , msg, " % c no esperado " , c);
			          error (msg);

                while (c! = ' \ n ' )
                    c = fgetc (archivo);    

                t. compLex = VACIO;
                ungetc (c, archivo);
            }
            romper ;
        }   
        m�s  si (c == ' t ' || c == ' T ' )
        {
            ungetc (c, archivo);
            fgets (aux, 5 , archivo); // ver si es nulo
            if ( strcmp (aux, " true " ) == 0 || strcmp (aux, " TRUE " ) == 0 )
            {
                t. compLex = PR_TRUE;
                strcpy (t. lexema , aux);
            }
            m�s
            {
                fprintf (salida, " % s  % s  % c " , msg, " % c no esperado " , c);
			          error (msg);

                while (c! = ' \ n ' )
                    c = fgetc (archivo);

                t. compLex = VACIO;
                ungetc (c, archivo);
            }
            romper ;
        }
        m�s  si (c! = EOF)
		    {
			      fprintf (salida, " % s  % s  % c " , msg, " % c no esperado " , c);
			      error (msg);
            while (c! = ' \ n ' )
                c = fgetc (archivo);
            strcpy (cont_esp, "  " );
            con = - 1 ; // variable que controla los espacios que se imprimen
            ungetc (c, archivo);
		    }
	 }
	si (c == EOF)
	{
		t. compLex = EOF;
		strcpy (t. lexema , " EOF " );
		// fprintf (salida, t.lexema, "EOF");
	}
}

int  main ( int argc, char * args [])
{
	salida = fopen ( " output.txt " , " w " );
	// como imprimir un \ n
	si (argc> 1 )
	{
		if (! (archivo = fopen (args [ 1 ], " rt " )))
		{
			fprintf (salida, " % s " , " Archivo no encontrado. \ n " );
			salida ( 1 );
		}
		while (t. compLex ! = EOF)
		{
			sigLex ();
            // preguntar si con> -1 para poder imprimir los espacios
            si (con> - 1 )
            {
                int j = 0 ;
                para (j = 0 ; j <= con; j ++)
                fprintf (salida, " % c " , cont_esp [j]);
            }
            interruptor (t. compLex )
			      {
                caso L_CORCHETE:
                    fprintf (salida, " % s " , " L_CORCHETE " );
                    romper ;
                caso R_CORCHETE:
                    fprintf (salida, " % s " , " R_CORCHETE " );
                    romper ;
                caso L_LLAVE:
                    fprintf (salida, " % s " , " L_LLAVE " );
                    romper ;
                caso R_LLAVE:
                    fprintf (salida, " % s " , " R_LLAVE " );
                    romper ;
                caso COMA:
                    fprintf (salida, " % s " , " COMA " );
                    romper ;
                caso DOS_PUNTOS:
                    fprintf (salida, " % s " , " DOS_PUNTOS " );
                    romper ;
                caso STRING:
                    fprintf (salida, " % s " , " STRING " );
                    romper ;
                N�MERO de caso :
                    fprintf (salida, " % s " , " N�MERO " );
                    romper ;
                caso PR_TRUE:
                    fprintf (salida, " % s " , " PR_TRUE " );
                    romper ;
                caso PR_FALSE:
                    fprintf (salida, " % s " , " PR_FALSE " );
                    romper ;
                caso PR_NULL:
                    fprintf (salida, " % s " , " PR_NULL " );
                    romper ;
                caso EOF:
                    // fprintf (salida, "% s", "EOF");
                    romper ;
            }
			
		}
		fclose (archivo);
	}
	m�s
	{
		fprintf (salida, " % s " , " Debe pasar como par�metro el camino al archivo fuente. \ n " );
		salida ( 1 );
	}
	fclose (salida);
	devuelve  0 ;
}