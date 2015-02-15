/*
 * IModule.h
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#ifndef IMODULE_H_
#define IMODULE_H_

class IModule
{
public:
	virtual ~IModule()
	{
	}
	virtual bool open() = 0;
	virtual void close() = 0;
	virtual void init() = 0;
};

#endif /* IMODULE_H_ */
