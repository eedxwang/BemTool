#ifndef LAPLACE_OP_HPP
#define LAPLACE_OP_HPP

#include "../calculus/calculus.hpp"
#include "../miscellaneous/specialfct.hpp"

using namespace std;
using bemtool::array;


/*===========================
  SIMPLE COUCHE LAPLACE EN 2D
  ===========================*/

template <typename PhiX, typename PhiY>
class BIOpKernel<LA,SL_OP,2,PhiX,PhiY>{
  
public: 
  typedef BIOpKernelTraits<LA,SL_OP,2,PhiX,PhiY> Trait;
  
private:
  const typename Trait::MeshX&   meshx;
  const typename Trait::MeshY&   meshy;    
        typename Trait::MatType  inter;
        typename Trait::JacX     dx;
        typename Trait::JacY     dy;
                        PhiX     phix;     
                        PhiY     phiy;
  const                 Real     kappa;
                        R3       x0_y0,x_y;
                        Real     h,r;
                        Cplx     ker; 
  
public:
  BIOpKernel<LA,SL_OP,2,PhiX,PhiY>(const typename Trait::MeshX& mx,
				   const typename Trait::MeshY& my,
				   const Real& k):
  meshx(mx), phix(mx), meshy(my), phiy(my), kappa(k) {};
  
  void Assign(const int& ix, const int& iy){
    const typename Trait::EltX& ex=meshx[ix];
    const typename Trait::EltY& ey=meshy[iy]; 
    x0_y0 = ex[0]-ey[0];
    dx    = MatJac(ex);
    dy    = MatJac(ey);
    h     = DetJac(ex)*DetJac(ey);
  }
  
  const typename Trait::MatType& operator()(const typename Trait::Rdx& tx,
					    const typename Trait::Rdy& ty){
    x_y  = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    ker = h*(-0.5/pi)*log(r);
    for(int j=0; j<Trait::nb_dof_x; j++){
      for(int k=0; k<Trait::nb_dof_y; k++){
	inter(j,k) = ker*phix(j,tx)*phiy(k,ty);
      }
    }
    return inter;
  }
  
  const Cplx& operator()(const typename Trait::Rdx& tx,
			 const typename Trait::Rdy& ty,
			 const int& kx, const int& ky){
    x_y  = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    ker = h*(-0.5/pi)*log(r);
    return ker *= phix(kx,tx)*phiy(ky,ty);
  }
  
  
};


typedef BIOpKernel<LA,SL_OP,2,P1_1D,P1_1D> LA_SL_2D_P1xP1;
typedef BIOpKernel<LA,SL_OP,2,P0_1D,P0_1D> LA_SL_2D_P0xP0;
typedef BIOpKernel<LA,SL_OP,2,P0_1D,P1_1D> LA_SL_2D_P0xP1;
typedef BIOpKernel<LA,SL_OP,2,P1_1D,P0_1D> LA_SL_2D_P1xP0;
typedef BIOpKernel<LA,SL_OP,2,P2_1D,P2_1D> LA_SL_2D_P2xP2;


/*===========================
  SIMPLE COUCHE LAPLACE EN 3D
  ===========================*/

template <typename PhiX, typename PhiY>
class BIOpKernel<LA,SL_OP,3,PhiX,PhiY>{
  
public: 
  typedef BIOpKernelTraits<LA,SL_OP,3,PhiX,PhiY> Trait;
  static const int EqType = LA;
  static const int OpType = SL_OP;  
  static const int Dim    = 3;    
  
private:
  const typename Trait::MeshX&   meshx;
  const typename Trait::MeshY&   meshy;    
        typename Trait::MatType  inter;
        typename Trait::JacX     dx;
        typename Trait::JacY     dy;
                        PhiX     phix;     
                        PhiY     phiy;
  const                 Real     kappa;
                        R3       x0_y0,x_y;
                        Real     h,r;
                        Cplx     ker;
  
public:
  BIOpKernel<LA,SL_OP,3,PhiX,PhiY>(const typename Trait::MeshX& mx,
				   const typename Trait::MeshY& my,
				   const Real& k):
  meshx(mx), phix(mx), meshy(my), phiy(my), kappa(k) {};
  
  void Assign(const int& ix, const int& iy){
    const typename Trait::EltX& ex=meshx[ix];
    const typename Trait::EltY& ey=meshy[iy]; 
    x0_y0 = ex[0]-ey[0];
    dx    = MatJac(ex);
    dy    = MatJac(ey);
    h     = DetJac(ex)*DetJac(ey);
  }
  
  const typename Trait::MatType& operator()(const typename Trait::Rdx& tx,
					    const typename Trait::Rdy& ty){
    x_y = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    ker = h/(4*pi*r);
    for(int j=0; j<Trait::nb_dof_x; j++){
      for(int k=0; k<Trait::nb_dof_y; k++){
	inter(j,k) = ker*phix(j,tx)*phiy(k,ty);
      }
    }
    return inter;
  }
  
  const Cplx& operator()(const typename Trait::Rdx& tx,
			 const typename Trait::Rdy& ty,
			 const int& kx, const int& ky){
    x_y = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    ker = h/(4*pi*r);
    return ker *= phix(kx,tx)*phiy(ky,ty);
  }
  
  
};

typedef BIOpKernel<LA,SL_OP,3,P1_2D,P1_2D> LA_SL_3D_P1xP1;
typedef BIOpKernel<LA,SL_OP,3,P0_2D,P0_2D> LA_SL_3D_P0xP0;
typedef BIOpKernel<LA,SL_OP,3,P0_2D,P1_2D> LA_SL_3D_P0xP1;
typedef BIOpKernel<LA,SL_OP,3,P1_2D,P0_2D> LA_SL_3D_P1xP0;
typedef BIOpKernel<LA,SL_OP,3,P2_2D,P2_2D> LA_SL_3D_P2xP2;


/*===========================
  DOUBLE COUCHE LAPLACE EN 2D
  ===========================*/

template <typename PhiX, typename PhiY>
class BIOpKernel<LA,DL_OP,2,PhiX,PhiY>{
  
public: 
  typedef BIOpKernelTraits<LA,DL_OP,2,PhiX,PhiY> Trait;
  
private:
  const typename Trait::MeshX&   meshx;
  const typename Trait::MeshY&   meshy;    
  const            vector<R3>&   normaly;
        typename Trait::MatType  inter;
        typename Trait::JacX     dx;
        typename Trait::JacY     dy;
                        PhiX     phix;     
                        PhiY     phiy;
  const                 Real     kappa;
                        R3       x0_y0,x_y,ny;
                        Real     h,r,r2;
                        Cplx     ker;
  
public:
  BIOpKernel<LA,DL_OP,2,PhiX,PhiY>(const typename Trait::MeshX& mx,
				   const typename Trait::MeshY& my,
				   const Real& k):
  meshx(mx), phix(mx), meshy(my), phiy(my), kappa(k),
    normaly(NormalTo(my)) {};
  
  void Assign(const int& ix, const int& iy){
    const typename Trait::EltX& ex=meshx[ix];
    const typename Trait::EltY& ey=meshy[iy]; 
    x0_y0 = ex[0]-ey[0];
    dx    = MatJac(ex);
    dy    = MatJac(ey);
    h     = DetJac(ex)*DetJac(ey);
    ny    = normaly[iy];
  }
  
  const typename Trait::MatType& operator()(const typename Trait::Rdx& tx,
					    const typename Trait::Rdy& ty){
    x_y = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    r2  = r*r;
    ker = -(h/r2)*(ny,x_y);
    for(int j=0; j<Trait::nb_dof_x; j++){
      for(int k=0; k<Trait::nb_dof_y; k++){
	inter(j,k) = ker*phix(j,tx)*phiy(k,ty);
      }
    }
    return inter;
  }

  const Cplx& operator()(const typename Trait::Rdx& tx,
			 const typename Trait::Rdy& ty,
			 const int& kx, const int& ky){
    x_y = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    r2  = r*r;
    ker = (-h/(2*pi*r2))*(ny,x_y);
    return ker *= phix(kx,tx)*phiy(ky,ty);
  }
  
  
};

typedef BIOpKernel<LA,DL_OP,2,P0_1D,P0_1D> LA_DL_2D_P0xP0;
typedef BIOpKernel<LA,DL_OP,2,P1_1D,P1_1D> LA_DL_2D_P1xP1;
typedef BIOpKernel<LA,DL_OP,2,P2_1D,P2_1D> LA_DL_2D_P2xP2;
typedef BIOpKernel<LA,DL_OP,2,P0_1D,P1_1D> LA_DL_2D_P0xP1;
typedef BIOpKernel<LA,DL_OP,2,P1_1D,P0_1D> LA_DL_2D_P1xP0;





/*===========================
  DOUBLE COUCHE LAPLACE EN 3D
  ===========================*/

template <typename PhiX, typename PhiY>
class BIOpKernel<LA,DL_OP,3,PhiX,PhiY>{
  
public: 
  typedef BIOpKernelTraits<LA,DL_OP,3,PhiX,PhiY> Trait;
  
private:
  const typename Trait::MeshX&        meshx;
  const typename Trait::MeshY&        meshy;    
        typename Trait::MatType       inter;
        typename Trait::JacX          dx;
        typename Trait::JacY          dy;
                        PhiX          phix;     
                        PhiY          phiy;
  const                 vector<R3>&   normaly;
  const                 Real          kappa;
                        R3            x0_y0,x_y,ny;
                        Real          h,r,r3;
                        Cplx          ker;
  
public:
  BIOpKernel<LA,DL_OP,3,PhiX,PhiY>(const typename Trait::MeshX& mx,
				   const typename Trait::MeshY& my,
				   const Real& k):
  meshx(mx), phix(mx), meshy(my), phiy(my), kappa(k),
    normaly(NormalTo(my)) {};
  
  void Assign(const int& ix, const int& iy){
    const typename Trait::EltX& ex=meshx[ix];
    const typename Trait::EltY& ey=meshy[iy]; 
    x0_y0 = ex[0]-ey[0];
    dx    = MatJac(ex);
    dy    = MatJac(ey);
    h     = DetJac(ex)*DetJac(ey);
    ny    = normaly[iy];
  }
  
  const typename Trait::MatType& operator()(const typename Trait::Rdx& tx,
					    const typename Trait::Rdy& ty){
    x_y = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    r3  = r*r*r;
    ker = (-h/(4*pi*r3))*(ny,x_y);
    for(int j=0; j<Trait::nb_dof_x; j++){
      for(int k=0; k<Trait::nb_dof_y; k++){
	inter(j,k) = ker*phix(j,tx)*phiy(k,ty);
      }
    }
    return inter;
  }

  const Cplx& operator()(const typename Trait::Rdx& tx,
			 const typename Trait::Rdy& ty,
			 const int& kx, const int& ky){    
    x_y = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    r3  = r*r*r; 
    ker = (-h/(4*pi*r3))*(ny,x_y);
    return ker *= phix(kx,tx)*phiy(ky,ty);
  }
  
};

typedef BIOpKernel<LA,DL_OP,3,P0_2D,P0_2D> LA_DL_3D_P0xP0;
typedef BIOpKernel<LA,DL_OP,3,P1_2D,P1_2D> LA_DL_3D_P1xP1;
typedef BIOpKernel<LA,DL_OP,3,P2_2D,P2_2D> LA_DL_3D_P2xP2;
typedef BIOpKernel<LA,DL_OP,3,P0_2D,P1_2D> LA_DL_3D_P0xP1;
typedef BIOpKernel<LA,DL_OP,3,P1_2D,P0_2D> LA_DL_3D_P1xP0;



/*===================================
  DOUBLE COUCHE ADJOINT LAPLACE EN 2D
  ===================================*/

template <typename PhiX, typename PhiY>
class BIOpKernel<LA,TDL_OP,2,PhiX,PhiY>{
  
public: 
  typedef BIOpKernelTraits<LA,TDL_OP,2,PhiX,PhiY> Trait;
  
private:
  const typename Trait::MeshX&        meshx;
  const typename Trait::MeshY&        meshy;    
        typename Trait::MatType       inter;
        typename Trait::JacX          dx;
        typename Trait::JacY          dy;
                        PhiX          phix;     
                        PhiY          phiy;
  const                 vector<R3>&   normalx;
  const                 Real          kappa;
                        R3            x0_y0,x_y,nx;
                        Real          h,r,r2;
                        Cplx          ker;
  
public:
  BIOpKernel<LA,TDL_OP,2,PhiX,PhiY>(const typename Trait::MeshX& mx,
				    const typename Trait::MeshY& my,
				    const Real& k):
  meshx(mx), phix(mx), meshy(my), phiy(my), kappa(k),
    normalx(NormalTo(mx)) {};
  
  void Assign(const int& ix, const int& iy){
    const typename Trait::EltX& ex=meshx[ix];
    const typename Trait::EltY& ey=meshy[iy]; 
    x0_y0 = ex[0]-ey[0];
    dx    = MatJac(ex);
    dy    = MatJac(ey);
    h     = DetJac(ex)*DetJac(ey);
    nx    = normalx[ix];
  }
  
  const typename Trait::MatType& operator()(const typename Trait::Rdx& tx,
					    const typename Trait::Rdy& ty){
    x_y = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    r2  = r*r;
    ker = (-h/(2*pi*r2))*(nx,x_y);
    for(int j=0; j<Trait::nb_dof_x; j++){
      for(int k=0; k<Trait::nb_dof_y; k++){
	inter(j,k) = ker*phix(j,tx)*phiy(k,ty);
      }
    }
    return inter;
  }

  const Cplx& operator()(const typename Trait::Rdx& tx,
			 const typename Trait::Rdy& ty,
			 const int& kx, const int& ky){    
    x_y = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    r2  = r*r;
    ker = -(h/r2)*(nx,x_y);
    return ker *= phix(kx,tx)*phiy(ky,ty);
  }
  
  
};

typedef BIOpKernel<LA,TDL_OP,2,P0_1D,P0_1D> LA_TDL_2D_P0xP0;
typedef BIOpKernel<LA,TDL_OP,2,P1_1D,P1_1D> LA_TDL_2D_P1xP1;
typedef BIOpKernel<LA,TDL_OP,2,P2_1D,P2_1D> LA_TDL_2D_P2xP2;
typedef BIOpKernel<LA,TDL_OP,2,P1_1D,P0_1D> LA_TDL_2D_P1xP0;
typedef BIOpKernel<LA,TDL_OP,2,P0_1D,P1_1D> LA_TDL_2D_P0xP1;




/*===================================
  DOUBLE COUCHE ADJOINT LAPLACE EN 3D
  ===================================*/

template <typename PhiX, typename PhiY>
class BIOpKernel<LA,TDL_OP,3,PhiX,PhiY>{
  
public: 
  typedef BIOpKernelTraits<LA,TDL_OP,3,PhiX,PhiY> Trait;
  
private:
  const typename Trait::MeshX&        meshx;
  const typename Trait::MeshY&        meshy;    
        typename Trait::MatType       inter;
        typename Trait::JacX          dx;
        typename Trait::JacY          dy;
                        PhiX          phix;     
                        PhiY          phiy;
  const                 vector<R3>&   normalx;
  const                 Real          kappa;
                        R3            x0_y0,x_y,nx;
                        Real          h,r,r3;
                        Cplx          ker;
  
public:
  BIOpKernel<LA,TDL_OP,3,PhiX,PhiY>(const typename Trait::MeshX& mx,
				    const typename Trait::MeshY& my,
				    const Real& k):
  meshx(mx), phix(mx), meshy(my), phiy(my), kappa(k),
    normalx(NormalTo(mx)) {};
  
  void Assign(const int& ix, const int& iy){
    const typename Trait::EltX& ex=meshx[ix];
    const typename Trait::EltY& ey=meshy[iy]; 
    x0_y0 = ex[0]-ey[0];
    dx    = MatJac(ex);
    dy    = MatJac(ey);
    h     = DetJac(ex)*DetJac(ey);
    nx    = normalx[ix];
  }
  
  const typename Trait::MatType& operator()(const typename Trait::Rdx& tx,
					    const typename Trait::Rdy& ty){
    x_y = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    r3  = r*r*r; 
    ker = (-h/(4*pi*r3))*(nx,x_y);
    for(int j=0; j<Trait::nb_dof_x; j++){
      for(int k=0; k<Trait::nb_dof_y; k++){
	inter(j,k) = ker*phix(j,tx)*phiy(k,ty);
      }
    }
    return inter;
  }


  const Cplx& operator()(const typename Trait::Rdx& tx,
			 const typename Trait::Rdy& ty,
			 const int& kx, const int& ky){    
    x_y = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    r3  = r*r*r; 
    ker = (-h/(4*pi*r3))*(nx,x_y);
    return ker *= phix(kx,tx)*phiy(ky,ty);
  }
  
  
};

typedef BIOpKernel<LA,TDL_OP,3,P0_2D,P0_2D> LA_TDL_3D_P0xP0;
typedef BIOpKernel<LA,TDL_OP,3,P1_2D,P1_2D> LA_TDL_3D_P1xP1;
typedef BIOpKernel<LA,TDL_OP,3,P2_2D,P2_2D> LA_TDL_3D_P2xP2;
typedef BIOpKernel<LA,TDL_OP,3,P0_2D,P1_2D> LA_TDL_3D_P0xP1;
typedef BIOpKernel<LA,TDL_OP,3,P1_2D,P0_2D> LA_TDL_3D_P1xP0;



/*============================
  HYPERSINGULIER LAPLACE EN 2D
  ============================*/

template <typename PhiX, typename PhiY>
class BIOpKernel<LA,HS_OP,2,PhiX,PhiY>{
  
public: 
  typedef BIOpKernelTraits<LA,HS_OP,2,PhiX,PhiY> Trait;
  
private:
  const typename Trait::MeshX&       meshx;
  const typename Trait::MeshY&       meshy;    
        typename Trait::MatType      inter;
        typename Trait::JacX         dx;
        typename Trait::JacY         dy;
        typename Trait::GradPhiX     grad_phix;
        typename Trait::GradPhiY     grad_phiy;
                        PhiX         phix;     
                        PhiY         phiy;
  const                 vector<R3>&  normalx;
  const                 vector<R3>&  normaly;
  const                 Real         kappa,kappa2;
                        R3           x0_y0,x_y,nx,ny;
                        Real         h,r;
                        Cplx         ker,val,val2;
  
public:
  BIOpKernel<LA,HS_OP,2,PhiX,PhiY>(const typename Trait::MeshX& mx,
				   const typename Trait::MeshY& my,
				   const Real& k):
  meshx(mx), phix(mx), grad_phix(mx), normalx(NormalTo(mx)),
    meshy(my), phiy(my), grad_phiy(my), normaly(NormalTo(my)),
    kappa(k), kappa2(kappa*kappa) {};
  
  void Assign(const int& ix, const int& iy){
    const typename Trait::EltX& ex=meshx[ix];
    const typename Trait::EltY& ey=meshy[iy]; 
    grad_phix.Assign(ix);
    grad_phiy.Assign(iy);    
    h     = DetJac(ex)*DetJac(ey);
    x0_y0 = ex[0]-ey[0];
    dx    = MatJac(ex);
    dy    = MatJac(ey);
    nx    = normalx[ix];
    ny    = normaly[iy];    
  }
  
  const typename Trait::MatType& operator()(const typename Trait::Rdx& tx,
					    const typename Trait::Rdy& ty){
    x_y = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    ker = h*(-0.5/pi)*log(r);
    for(int j=0; j<Trait::nb_dof_x; j++){
      for(int k=0; k<Trait::nb_dof_y; k++){
	inter(j,k) = ( vprod(nx,grad_phix(j,tx)),vprod(ny,grad_phiy(k,ty)) )*ker;
      }
    }
    return inter;
  }
  
  const Cplx& operator()(const typename Trait::Rdx& tx,
			 const typename Trait::Rdy& ty,
			 const int& kx, const int& ky){
    x_y  = x0_y0 + dx*tx-dy*ty;
    r    = norm2(x_y);
    ker  = h*(-0.5/pi)*log(r);
    ker *= ( vprod(nx,grad_phix(kx,tx)),vprod(ny,grad_phiy(ky,ty)) );
    return ker;
  }
  
  
  
};

typedef BIOpKernel<LA,HS_OP,2,P1_1D,P1_1D> LA_HS_2D_P1xP1;
typedef BIOpKernel<LA,HS_OP,2,P2_1D,P2_1D> LA_HS_2D_P2xP2;


/*============================
  HYPERSINGULIER LAPLACE EN 3D
  ============================*/

template <typename PhiX, typename PhiY>
class BIOpKernel<LA,HS_OP,3,PhiX,PhiY>{
  
public: 
  typedef BIOpKernelTraits<LA,HS_OP,3,PhiX,PhiY> Trait;
  
private:
  const typename Trait::MeshX&       meshx;
  const typename Trait::MeshY&       meshy;    
        typename Trait::MatType      inter;
        typename Trait::JacX         dx;
        typename Trait::JacY         dy;
        typename Trait::GradPhiX     grad_phix;
        typename Trait::GradPhiY     grad_phiy;
                        PhiX         phix;     
                        PhiY         phiy;
  const                 vector<R3>&  normalx;
  const                 vector<R3>&  normaly;
  const                 Real         kappa,kappa2;
                        R3           x0_y0,x_y,nx,ny;
                        Real         h,r;
                        Cplx         ker,val,val2;
  
public:
  BIOpKernel<LA,HS_OP,3,PhiX,PhiY>(const typename Trait::MeshX& mx,
				   const typename Trait::MeshY& my,
				   const Real& k):
  meshx(mx), phix(mx), grad_phix(mx), normalx(NormalTo(mx)),
    meshy(my), phiy(my), grad_phiy(my), normaly(NormalTo(my)),
    kappa(k), kappa2(kappa*kappa) {};
  
  void Assign(const int& ix, const int& iy){
    const typename Trait::EltX& ex=meshx[ix];
    const typename Trait::EltY& ey=meshy[iy]; 
    grad_phix.Assign(ix);
    grad_phiy.Assign(iy);    
    h     = DetJac(ex)*DetJac(ey);
    x0_y0 = ex[0]-ey[0];
    dx    = MatJac(ex);
    dy    = MatJac(ey);
    nx    = normalx[ix];
    ny    = normaly[iy];    
  }
  
  const typename Trait::MatType& operator()(const typename Trait::Rdx& tx,
					    const typename Trait::Rdy& ty){
    x_y = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    ker = h/(4*pi*r);
    for(int j=0; j<Trait::nb_dof_x; j++){
      for(int k=0; k<Trait::nb_dof_y; k++){
	inter(j,k) = ( vprod(nx,grad_phix(j,tx)),vprod(ny,grad_phiy(k,ty)) )*ker;
      }
    }
    return inter;
  }
  
  const Cplx& operator()(const typename Trait::Rdx& tx,
			 const typename Trait::Rdy& ty,
			 const int& kx, const int& ky){
    x_y = x0_y0 + dx*tx-dy*ty;
    r   = norm2(x_y);
    ker = h/(4*pi*r);
    return ker *= ( vprod(nx,grad_phix(kx,tx)),vprod(ny,grad_phiy(ky,ty)) );    
  }
  
  
};


typedef BIOpKernel<LA,HS_OP,3,P1_2D,P1_2D> LA_HS_3D_P1xP1;
typedef BIOpKernel<LA,HS_OP,3,P2_2D,P2_2D> LA_HS_3D_P2xP2;



















#endif