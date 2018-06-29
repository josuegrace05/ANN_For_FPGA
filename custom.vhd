LIBRARY ieee;

USE ieee.numeric_std.all;
USE ieee.std_logic_1164.all

ENTITY custom IS
    PORT ( 
        signal dataa: in std_logic_vector(31 downto 0)
        signal datab: in std_logic_vector(31 downto 0)    -- optional
        signal result: out std_logic_vector(31 downto 0)  -- result (always required)
    );
END ENTITY custom;

ARCHITECTURE main OF custom IS
BEGIN
END main;
