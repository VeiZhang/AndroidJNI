package com.excellence.androidjni;

/**
 * Created by ZhangWei on 2016/12/14.
 */

public class Info
{
	public String name;
	public int id;

	public Info()
	{

	}

	public Info(String name, int id)
	{
		this.name = name;
		this.id = id;
	}

	@Override
	public String toString()
	{
		return "Info{" + "name='" + name + '\'' + ", id=" + id + '}';
	}
}
