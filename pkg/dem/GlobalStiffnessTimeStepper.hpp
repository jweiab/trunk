/*************************************************************************
*  Copyright (C) 2006 by Bruno Chareyre                                  *
*  bruno.chareyre@hmg.inpg.fr                                            *
*                                                                        *
*  This program is free software; it is licensed under the terms of the  *
*  GNU General Public License v2 or later. See file LICENSE for details. *
*************************************************************************/

#pragma once

#include<yade/core/TimeStepper.hpp>


/*! \brief Compute the critical timestep of the leap-frog scheme based on global stiffness of bodies
	See usage details in TriaxialTest documentation (TriaxialTest is also a good example of how to use this class)
 */

class Interaction;
class BodyContainer;
class Scene;

class GlobalStiffnessTimeStepper : public TimeStepper
{
	private :
		vector<Vector3r> stiffnesses;
		vector<Vector3r> Rstiffnesses;
		void computeStiffnesses(Scene*);

		Real		newDt;
		bool		computedSomething,
 				computedOnce;
		void findTimeStepFromBody(const shared_ptr<Body>& body, Scene * ncb);
	
	public :
		virtual ~GlobalStiffnessTimeStepper();
	
		virtual void computeTimeStep(Scene*);
		virtual bool isActivated();
		YADE_CLASS_BASE_DOC_ATTRS_CTOR(
			GlobalStiffnessTimeStepper,TimeStepper,"An engine assigning the time-step as a fraction of the minimum eigen-period in the problem",
			((Real,defaultDt,-1,,"used as the initial value of the timestep (especially useful in the first steps when no contact exist). If negative, it will be defined by :yref:`utils.PWaveTimeStep` * :yref:`GlobalStiffnessTimeStepper::timestepSafetyCoefficient`"))
			((Real,maxDt,Mathr::MAX_REAL,,"if positive, used as max value of the timestep whatever the computed value"))
			((Real,previousDt,1,,"last computed dt |yupdate|"))
			((Real,timestepSafetyCoefficient,0.8,,"safety factor between the minimum eigen-period and the final assigned dt (less than 1))"))
			((bool,densityScaling,false,,"|yupdate| don't modify this value. see :yref:`NewtonIntegrator::densityScaling` and :yref:`NewtonIntegrator::densityScaling`"))
			((Real,targetDt,1,,"if :yref:`NewtonIntegrator::densityScaling` is active, this value will be used as the simulation  timestep and the scaling will use this value of dt as the target value. The value of targetDt is arbitrary and should have no effect in the result in general. However if some bodies have imposed velocities, for instance, they will move more or less per each step depending on this value.")),
			computedOnce=false;)
		DECLARE_LOGGER;
};

REGISTER_SERIALIZABLE(GlobalStiffnessTimeStepper);


