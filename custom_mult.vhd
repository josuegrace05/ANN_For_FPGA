LIBRARY ieee;

USE ieee.numeric_std.all;
USE ieee.std_logic_1164.all

ENTITY custom_mult IS
    PORT ( 
        signal dataa: in std_logic_vector(31 downto 0)
        signal datab: in std_logic_vector(31 downto 0)    -- optional
        signal result: out std_logic_vector(31 downto 0)  -- result (always required)
    );
END ENTITY custom_mult;

ARCHITECTURE mult OF custom_mult IS
BEGIN
	return <= std_logic_vector(signed(dataa(31 downto 0) * signed(datab(31 downto 0));
END mult;
