#include "WPILib.h"
#include <math.h>
#include <memory>

using std::shared_ptr;

class Robot: public IterativeRobot, public PIDOutput
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;

	CANTalon *leftdrive1 = new CANTalon(0);
	CANTalon *leftdrive2= new CANTalon(1);
	CANTalon *rightdrive1 = new CANTalon(2);
	CANTalon *rightdrive2= new CANTalon(3);
	CANTalon *shooterMotor1 = new CANTalon(4);
	CANTalon *shooterMotor2 = new CANTalon(5);
	CANTalon *intakeMotor = new CANTalon(6);

	RobotDrive *drive = new RobotDrive(leftdrive2, leftdrive1, rightdrive2,
			rightdrive1);

	Joystick *controlstick = new Joystick(2);
	Joystick *leftjoystick = new Joystick(0);
	Joystick *rightjoystick = new Joystick(1);

  PowerDistributionPanel *pdp = new PowerDistributionPanel(0);


	void RobotInit() override
	{
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);
	}
	double rotateRate = 0;
	void PIDWrite(float output) { // Implement PIDOutput
		rotateRate = output;
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit()
	{
		autoSelected = *((std::string*)chooser->GetSelected());
		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}

	void AutonomousPeriodic()
	{
		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}

	void TeleopInit()
	{
		drive->SetExpiration(200000);
		drive->SetSafetyEnabled(false);
		liftdown->Set(false);
	}

  double speed;
  Timer *timer1 = new Timer();
	Timer *timre2 = new Timer();

	void TeleopPeriodic()
	{
		speed = leftJoystick->GetRawButton(1) ? 1 : 0.5;
		drive->TankDrive(leftjoystick->GetY() * speed, rightjoystick->GetY() * speed);
		if(controlstick->GetRawButton(2))
		{
			timer1->Reset();
			timer1->Start();
			PickBall();
		}
		if(controlstick->GetRawButton(1))
		{
			timer2->Reset();
			timer2->Start();
			ShootBall();
		}
		if(timer1->Get() >= 1)
		{
			intakeMotor->Set(0);
		}
		if(timer2->Get() >= .5)
		{
			shooterMotor1->Set(0);
			shooterMotor2->Set(0);
		}
	}

	void TestPeriodic()
	{
		lw->Run();
	}

	void PickBall()
	{
		intakeMotor->Set(1);
	}

	void ShootBall()
	{
		shooterMotor1->Set(1); // maybe reverse one motor if needed
		shooterMotor2->Set(1);
	}
};

START_ROBOT_CLASS(Robot)
