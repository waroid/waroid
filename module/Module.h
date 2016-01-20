/*
 * Module.h
 *
 *  Created on: 2015. 2. 13.
 *      Author: mirime
 */

#ifndef MODULE_H_
#define MODULE_H_

class IModule
{
public:
	virtual ~IModule()
	{
	}

	virtual const char* getDescription() const = 0;
	virtual bool open() = 0;
	virtual void close() = 0;
	virtual void init() = 0;
};

#endif /* MODULE_H_ */
