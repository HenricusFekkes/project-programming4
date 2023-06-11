#pragma once


namespace  dae
{
	class ICommand
	{
	public:
		ICommand() = default;
		virtual ~ICommand() = default;
		ICommand(const ICommand& other) = delete;
		ICommand(ICommand&& other) = delete;
		ICommand& operator=(const ICommand& other) = delete;
		ICommand& operator=(ICommand&& other) = delete;

		virtual bool Execute() = 0;
	};
}
