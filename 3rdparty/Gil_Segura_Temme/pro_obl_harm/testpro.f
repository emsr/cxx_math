      PROGRAM SPHEROIDAL
      IMPLICIT REAL*8 (A-H,O-Z)
      DIMENSION PL(0:2001),QL(0:2001)
      NMAX=2000
      M=2500
      MODE=2
      OPEN(10,FILE='data.dat',STATUS='NEW')
      WRITE(10,*)'PROLATE HARMONICS, M=2500, NMAX=2000, MODE 2' 
      WRITE(10,*)
      WRITE(10,*)'PL2(N)=PL(N)/(X*X-1.)**M/2/(2M-1)!!*10**(-290)'
      WRITE(10,*)'QL2(N)=QL(N)*(X*X-1.)**M/2/(2M)!!*10**(290)'
      WRITE(10,*)
      WRITE(10,30)'X','N','PL2(N)', 
     & 'QL2(N)','QL2(0)'
      WRITE(10,*) 
      DO X=1.2D0,10.D0,1.6D0
         CALL DPROH(X,M,NMAX,MODE,PL,QL,NUEVO)
         WRITE(10,800) X,NUEVO,PL(NUEVO),QL(NUEVO),QL(0)
         NM=10
         WRITE(10,800) X,NM,PL(NM),QL(NM),QL(0)
      END DO
      M=120
      MODE=1
      WRITE(10,*)
      WRITE(10,*)'PROLATE HARMONICS, M=120, NMAX=2000, MODE 1' 
      WRITE(10,*) 
      WRITE(10,31)'X','N','PL(N)/(2M-1)!!', 
     &             'QL(N)/(2M)!!','QL(0)/(2M)!!'
      WRITE(10,*)
      DO X=1.2D0,10.D0,1.6D0
         CALL DPROH(X,M,NMAX,MODE,PL,QL,NUEVO)
         WRITE(10,800) X,NUEVO,PL(NUEVO),QL(NUEVO),QL(0)
         NM=10
         WRITE(10,800) X,NM,PL(NM),QL(NM),QL(0)
      END DO
      WRITE(10,*)
      NMAX=2000
      M=50
      MODE=0
      WRITE(10,*)'OBLATE HARMONICS, M=50, NMAX=2000, MODE 0'
      WRITE(10,*) 
      WRITE(10,32)'X','N', 'RL(N)', 'TL(N)', 'TL(0)'
      WRITE(10,*)
      DO X=0.2D0,10.D0,1.6D0
         CALL DOBLH(X,M,NMAX,MODE,PL,QL,NUEVO)
         WRITE(10,801) X,NUEVO,PL(NUEVO),QL(NUEVO),QL(0)
         NM=10
         WRITE(10,801) X,NM,PL(NM),QL(NM),QL(0)
      ENDDO
      WRITE(10,*)
   30 FORMAT (4X,A1,3X,A1,2X,3(8X,A7)) 
   31 FORMAT (4X,A1,3X,A1,5X,A14,2(2X,A14)) 
   32 FORMAT (4X,A1,3X,A1,3(9X,A6))   
  800 FORMAT (F6.1,1X,I4,1X,3D16.9)
  801 FORMAT (F6.1,1X,I4,1X,3D16.9)
      CLOSE(10)
      END

         SUBROUTINE DPROH(X,M,NMAX,MODE,PL,QL,NUEVO)
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C  INPUT :                                                                C
C                                                                         C  
C    X        ARGUMENT OF THE FUNCTIONS                                   C
C                                                                         C
C    M        DEGREE OF THE SPHEROIDAL HARMONICS                          C
C                                                                         C
C    NMAX     MAXIMUM ORDER OF THE FUNCTIONS :                            C
C             WE SHALL GET  FUNCTIONS OF ALL THE ORDERS BELOW             C
C             MIN(NMAX,NUEVO). NUEVO IS DEFINED BELOW .                   C
C                                                                         C
C    MODE      MODE OF CALCULATION   (SEE OUTPUT)                         C
C                                                                         C
C  OUTPUT :                                                               C
C                                                                         C
C    *IF MODE IS EQUAL TO 0:                                              C
C                                                                         C
C    PL(L+1)                                                              C
C             WE SHALL KEEP THESE VALUES IN AN ARRAY                      C
C    QL(L+1)                                                              C
C             WE SHALL KEEP THESE VALUES IN AN ARRAY                      C
C    NUEVO    MAXIMUM ORDER OF  FUNCTIONS CALCULATED WHEN                 C
C             PL (NMAX+1) IS LARGER THAN 1/TINY. TINY IS                  C
C             DEFINED BELOW.                                              C
C                                                                         C
C                                                                         C
C                                                                         C
C   *IF MODE IS EQUAL TO 1:                                               C
C                                                                         C
C    PL(L+1)/(2M-1)!!                                                     C
C             WE SHALL KEEP THESE VALUES IN AN ARRAY                      C
C    QL(L+1)/(2M)!!                                                       C
C             WE SHALL KEEP THESE VALUES IN AN ARRAY                      C
C    NUEVO    MAXIMUM ORDER OF  FUNCTIONS CALCULATED WHEN                 C
C             PL (NMAX+1)/(2M-1)!!  IS LARGER THAN 1/TINY .               C
C             TINY IS DEFINED BELOW.                                      C
C                                                                         C
C    *IF MODE IS EQUAL TO 2:                                              C
C                                                                         C
C    PL(L+1)*TINY/(2M-1)!!/(X*X-1)**(M/2)                                 C
C             WE SHALL KEEP THESE VALUES IN AN ARRAY                      C
C    QL(L+1)*(X*X-1)**(M/2)/(2M)!!/TINY                                   C
C             WE SHALL KEEP THESE VALUES IN AN ARRAY                      C
C    NUEVO    MAXIMUM ORDER OF  FUNCTIONS CALCULATED WHEN                 C
C             (NMAX+1)*PL(NMAX) IS LARGER THAN 1/TINY .                   C
C             TINY IS DEFINED BELOW.                                      C
C                                                                         C 
C                                                                         C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                         C
C   DECLARATION OF VARIABLES                                              C
C                                                                         C
c                                                                         C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
       IMPLICIT REAL*8 (A-H,O-Z)
       DIMENSION PL(0:NMAX+1),QL(0:NMAX+1)
       PARAMETER(PI=3.14159265358979323D0,EPS=1.D-16,TINY=1.D-290)
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C   EPS: REQUIRED ACCURACY FOR THE CONTINUED FRACTION (LENTZ-THOMPSON)   C
C   TINY: SMALL PARAMETER CLOSE TO THE UNDERFLOW LIMIT                   C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
       OVER=1.D0/TINY
       TINYSQ=DSQRT(TINY)
       IF (X.LE.1.D0) THEN
          WRITE(6,*)'IMPROPER ARGUMENT. X MUST BE GREATER THAN 1'
          STOP
       END IF
       FL=M/2.
       IF (FLOAT(INT(FL)).EQ.FL) THEN
           AR=1.
       ELSE
           AR=-1.
       END IF      
       DZM=DSQRT(X*X-1.D0)
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                         C
C   WE USE THE CODE IF NMAX IS GREATER THAN OR EQUAL TO 2                 C
C                                                                         C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
       NMAXP=NMAX
       IF(NMAX.LT.2) NMAX=2
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                         C
C   WE STORE THE VALUES OF PL(0) AND PL(1)                                C
C                                                                         C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
       PL0=1.D0 
       IF (MODE.EQ.0) THEN
         IF (M.GT.0) THEN  
           J=1 
              DO I=1,M
               PL0=PL0*DZM*(2.*M-J)
               J=J+2
              END DO  
         END IF
         PL(0)=PL0
         PL(1)=X*(2.*M+1.D0)*PL(0)
       ELSE IF (MODE.EQ.1) THEN
         IF (ABS(M*DLOG(DZM)).GT.(DLOG(OVER))) THEN
              WRITE(6,*)'BETTER TRY MODE=2'
              STOP
         END IF  
         IF (M.GT.0) THEN
              DO I=1,M
               PL0=PL0*DZM
              END DO 
         END IF
         PL(0)=PL0
         PL(1)=X*(2.*M+1.D0)*PL(0)
       ELSE
         PL(0)=PL0*TINY    
         PL(1)=X*(2.*M+1.D0)*PL(0)
       END IF
       NP=1
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                         C
C   WE USE THE RECURRENCE RELATIONS                                       C
C                                                                         C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
       DO WHILE ((NP.LE.NMAX).AND.(ABS((NP+1.D0)*PL(NP)).LT.OVER))
        PL(NP+1)=((2.D0*(NP+M)+1.D0)*X*PL(NP)-(NP+M+M)*
     &               PL(NP-1))/(NP+1.D0)
        NP=NP+1
       ENDDO
       NMAX=NP-1
       IF (MODE.EQ.0) THEN         
         FACTOR=FACTCO(NMAX,PL(NMAX+1),M,OVER)        
         DO WHILE ((FACTOR.EQ.0.D0).AND.(NMAX.GT.0)) 
          NMAX=NMAX-3
          FACTOR=FACTCO(NMAX,PL(NMAX+1),M,OVER)
         END DO   
         IF (NMAX.LE.0.) THEN
           WRITE(6,*)'TRY ANOTHER M'
           STOP
         END IF
       ELSE
         FACTOR=FACTCONEW(NMAX,PL(NMAX+1),M)
       END IF         
       NUEVO=NMAX      
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                         C
C   WE EVALUATE THE CONTINUED FRACTION USING                              C
C   LENTZ-THOMPSON ALGORITHM                                              C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
       N=NMAX
       MM=0
       B=(1.D0+(N+2.D0)/(M+M+N+1.D0) )*X
       A=1.D0
       FC=TINYSQ
       C0=FC
       D0=0.D0
10     D0=B+A*D0
       IF (DABS(D0).LT.TINYSQ) D0=TINYSQ
       C0=B+A/C0
       IF (DABS(C0).LT.TINYSQ) C0=TINYSQ
       D0=1./D0
       DELTA=C0*D0
       FC=FC*DELTA
       MM=MM+1
       A=-(N+MM+1.D0)/DFLOAT(N+M+M+MM) 
       B=(1.D0+(N+MM+2.D0)/(M+M+N+MM+1.D0))*X   
       IF (ABS(DELTA-1.D0).GT.EPS) GOTO 10
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                         C
C     WE EVALUATE QL(NMAX+1) AND QL(NMAX) USING :                         C
C     THE WRONSKIAN : W{PL(NMAX),QL(NMAX)} =1./(1.-X**2)                  C
C     THE KNOWN VALUES OF PL(NMAX+1) AND PL(NMAX)                         C
C     THE VALUE OF H = QL(NMAX+1)/QL(NMAX)                                C
C                                                                         C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
       QL(NMAX)=AR*FACTOR/(1.D0-FC*PL(NMAX)/PL(NMAX+1))
       QL(NMAX+1)=QL(NMAX)*FC
       DO I=1,NMAX
        NP=NMAX+1-I
        N=NP-1
        QL(N)=((NP+NP+M+M+1.D0)*X*QL(NP)-(NP+1.D0)*QL(NP+1))
     &           /DFLOAT(NP+M+M)
       ENDDO
       NMAX=NMAXP
       RETURN
       END
